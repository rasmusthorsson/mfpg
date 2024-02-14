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
#include "configs.h"

#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>

using namespace noteenums;
using namespace std;

using Node_Tuple = std::tuple<int, int, int>;
using Distance = int;

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
		("t,test", "Select test parameters.", cxxopts::value<int>())
		("v,verbose", "Make output more verbose.") //TODO
		("o,output", "Specify where the output should be written.",
						cxxopts::value<std::string>())
		;
	options.parse_positional({"score"});

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << "\n";
		return 0;
	}
	if (result.count("version")) {
		std::cout << "mfpr version: " << VERSION_MFPG << "\n";
		return 0;
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
	

	IString G_s(1, Note::G_3, Note::Gs_5);
	IString D_s(2, Note::D_4, Note::Ds_6);
	IString A_s(3, Note::A_4, Note::As_6);
	IString E_s(4, Note::E_5, Note::F_7);
	
	std::vector<IString> strings{G_s, D_s, A_s, E_s};

	NoteMapper<Node_Tuple>* note_mapper = new BasicNoteMapper(strings);
	ActionSet<Node_Tuple, Distance> action_set;
	if (result.count("test")) {
		if (result["test"].as<int>() == 1) {
			action_set = configs::test_configuration_1();
		} else if (result["test"].as<int>() == 2) { 
			action_set = configs::test_configuration_2();
		}
	} else {
		action_set = configs::test_configuration_1();
	}

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
		delete(solver);
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
			delete(solver);
			return -1;
		}
		configs::writeOutput(out, solver, result["csv"].as<bool>());
		out.close();
	} else {
		ostream out(std::cout.rdbuf());
		configs::writeOutput(out, solver, result["csv"].as<bool>());
	}
	delete solver;
	return 0;
}
