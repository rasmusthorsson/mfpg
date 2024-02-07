#include "mx/api/ScoreData.h"
#include "mx/api/DocumentManager.h"

#include "cxxopts.hpp"

#include "NoteEnums.h"
#include "IString.h"
#include "BasicNoteMapper.h"
#include "Action.h"
#include "ActionSet.h"
#include "LayerList.h"
#include "NoteList.h"
#include "NoteMapper.h"
#include "GraphSolver.h"
#include "GreedySolver.h"
#include "Instrument.h"
#include "conf_cmake.h"

#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>

using namespace noteenums;
using namespace std;

using Node_Tuple = std::tuple<int, int, int>;
using Distance = int;

//TODO Rewrite this to not depend on tuple choice
void writeOutput(ostream& out, GraphSolver<Node_Tuple, Distance>* solver, bool csv) {
	int count = 1;
	if (csv) {
		out << "note number, note, string, finger, hp, cost, combinations\r\n";
		for (auto sol : solver->getSolution()) {
			out << count << ","
			    << get<0>(sol).getNote() << ","
			    << get<0>(get<0>(sol).getState()) << ","
			    << get<2>(get<0>(sol).getState()) << ","
			    << get<1>(get<0>(sol).getState()) << ","
			    << get<1>(sol) << ","
			    << get<0>(sol).getLayerList().getSize() << "\r\n";
			count++;
		}
	} else {
		for (auto sol : solver->getSolution()) {
			out << "Note number: " << count << "\n";
			out << "Note: " << get<0>(sol).getNote() << "\n";
			out << "String: " << get<0>(get<0>(sol).getState())
			    << ", Finger: " << get<2>(get<0>(sol).getState())
			    << ", Hand Position: " 
			    << get<1>(get<0>(sol).getState()) << "\n"
			    << "Distance of transition: " << get<1>(sol) << "\n"
			    << "Amount of possible fingerings: " 
			    << get<0>(sol).getLayerList().getSize() << "\n"
			    << "------------------------------------" << "\n";
			count++;
		}
	}
}

int main (int argc, char *argv[]) {

//-------------------------------- Input/Arguments -------------------------
	cxxopts::Options options("mfpr");
	options.positional_help("[optional args]").show_positional_help();
	options.add_options()
		("score", "Input file in musicXML format.", 
						cxxopts::value<std::string>())
		("version", "Shows program version.")
		("greedy", "Use GreedySolver instead of standard solver, for testing.")
		("h,help", "Show this message.")
		("c,csv", "Structure output as CSV.") 
		("v,verbose", "Make output more verbose.") //TODO
		("o,output", "Specify where the output should be written.",
						cxxopts::value<std::string>())
		;
	options.parse_positional({"score"});

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << "\n";
		return -1;
	}
	if (result.count("version")) {
		std::cout << "mfpr version: " << VERSION_MFPG << "\n";
		return -1;
	}
	ifstream input_file;
	if (result.count("score")) {
		auto file_path = result["score"].as<std::string>();
		input_file.open(file_path);
		if (!input_file.is_open()) {
			cout << "Could not open file: " << argv[1] << "\n";
			return -1;
		}
	} else {
		std::cout << "No musicXML file found, please supply a musicXML file "
			     "to process.\n";
		return -1;
	}

	string buffer;
	string sheet_music;
	while (input_file) {
		getline(input_file, buffer);
		sheet_music = sheet_music + "\r\n" + buffer;
	}
	input_file.close();

//------------------------- MX conversion --------------------------------

	using namespace mx::api;

	auto& mgr = DocumentManager::getInstance();

	istringstream istr{sheet_music};
	const auto documentID = mgr.createFromStream(istr);
	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	NoteList note_list(score);

//---------------------- Instrument creation ----------------------------
	
	typedef std::tuple<bool, Distance> (*action_type) (Node_Tuple, Node_Tuple);

	IString G_s(1, Note::G_3, Note::Gs_5);
	IString D_s(2, Note::D_4, Note::Ds_6);
	IString A_s(3, Note::A_4, Note::As_6);
	IString E_s(4, Note::E_5, Note::F_7);
	
	std::vector<IString> strings{G_s, D_s, A_s, E_s};

	NoteMapper<Node_Tuple>* note_mapper = new BasicNoteMapper(strings);

	action_type to_rest = [] (Node_Tuple t1, Node_Tuple t2) {
		if (t2 == Node_Tuple{0, 0, 0}) {
			return std::tuple<bool, Distance>{true, 0};
		}
		return std::tuple<bool, Distance>{false, 0};
	};
	action_type HP_action = [] (Node_Tuple t1, Node_Tuple t2) {
		int out = std::abs(std::get<1>(t1) - std::get<1>(t2));
		return std::tuple<bool, Distance>{true, out};
	};
	action_type finger_action = [] (Node_Tuple t1, Node_Tuple t2) {
		int out = std::abs(std::get<2>(t1) - std::get<2>(t2));
		return std::tuple<bool, Distance>{true, out};
	};
	action_type string_action_no_rest = [] (Node_Tuple t1, Node_Tuple t2) {
		int out = 0;
		if (std::abs(std::get<0>(t1) - std::get<0>(t2)) >= 2) {
			out = out + 100;
		} else {
			out = out + std::abs(std::get<0>(t1) - std::get<0>(t2));
		}
		return std::tuple<bool, Distance>{true, out};
	};
	action_type string_action_rest = [] (Node_Tuple t1, Node_Tuple t2) {
		int out = std::abs(std::get<0>(t1) - std::get<0>(t2));
		return std::tuple<bool, Distance>{true, out};
	};
	action_type rest = [] (Node_Tuple t1, Node_Tuple t2) {
		if (t1 == Node_Tuple{0, 0, 0} || t2 == Node_Tuple{0, 0, 0}) {
			return std::tuple<bool, Distance>{true, 0};
		}
		return std::tuple<bool, Distance>{false, 0};
	};
	
	Action<Node_Tuple, Distance> to_r(to_rest, "to_rest");
	Action<Node_Tuple, Distance> r(rest, "rest"); 
	Action<Node_Tuple, Distance> s_a_NR(string_action_no_rest, 
							"string_action_no_rest");
	Action<Node_Tuple, Distance> s_a_R(string_action_rest, "string_action_rest");
	Action<Node_Tuple, Distance> f_a(finger_action, "finger_action");
	Action<Node_Tuple, Distance> hp_a(HP_action, "hand_position_action");

	ActionSet<Node_Tuple, Distance> action_set({
						{to_r, true},
						{r, true},
						{s_a_NR, true},
						{s_a_R, false},
						{f_a, true}, 
						{hp_a, true}
						});

	action_set.addDependency("string_action_no_rest", "rest", false);
	action_set.addDependency("string_action_rest", "rest", true);
	action_set.addDependency("rest", "to_rest", false);
	action_set.addDependency("string_action_no_rest", "to_rest", false);
	action_set.addDependency("finger_action", "to_rest", false);
	action_set.addDependency("hand_position_action", "to_rest", false);

	Instrument<Node_Tuple, Distance> violin(strings, note_mapper, action_set);

//-------------------------- Graph building/solving -------------------------

	LayerList<Node_Tuple, Distance> list(note_list, violin.getNoteMapper());
	delete note_mapper;
	list.buildTransitions(violin.getActionSet());
	
	GraphSolver<Node_Tuple, Distance>* solver;
	if (result.count("greedy")) {
		solver = new GreedySolver();
	} else {
		std::cout << "Defaulting to greedysolver as no other solver is "
			     "available." << "\n";
		solver = new GreedySolver();
	}
	try {
		solver->solve(list);
	} catch (SolverException e) {
		std::cout << e.what() << "\n";
		return -1;
	}

//------------------------------ Output ----------------------------------
	if (result.count("output")) {
		auto out_file = result["output"].as<std::string>();
		ofstream out;
		out.open(out_file, std::ofstream::binary);
		if (!out.is_open()) {
			std::cout << "Failed to open file: " << out_file << 
				     ", Aborting..." << "\n";
			return -1;
		}
		writeOutput(out, solver, result["csv"].as<bool>());
		out.close();
	} else {
		ostream out(std::cout.rdbuf());
		writeOutput(out, solver, result["csv"].as<bool>());
	}
	delete solver;
	return 1;
}

