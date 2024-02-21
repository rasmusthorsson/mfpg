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
		("score", "Input file in musicXML format.", cxxopts::value<std::string>())
		("version", "Shows program version.")
		("greedy", "Use GreedySolver instead of standard solver, for testing.")
		("h,help", "Show this message.")
		("c,csv", "Structure output as CSV.")
		("t,test", "Select test parameters.", cxxopts::value<int>())
		("v,verbose", "Make output more verbose.", cxxopts::value<int>())
		("o,output", "Specify where the output should be written.",cxxopts::value<std::string>());
	options.parse_positional({"score"});

	ostream& log = std::cout;

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << "\n";
		return 0;
	}

	if (result.count("version")) {
		std::cout << "mfpr version: " << VERSION_MFPG << "\n";
		return 0;
	}

	if (result.count("verbose")) {
		configs::MyLog::verbose_out(log, "Verbose option set: " + 
				(to_string(result["verbose"].as<int>())) + "\n", 
				configs::VERBOSE_LEVEL::VERBOSE_ALL);
		configs::VERBOSE = static_cast<configs::VERBOSE_LEVEL>(result["verbose"].as<int>());
	}

	ifstream input_file;

	if (result.count("score")) {
		auto file_path = result["score"].as<std::string>();
		input_file.open(file_path);
		if (!input_file.is_open()) {
			configs::MyLog::verbose_out(log, ("ERROR: Could not open file: " + 
				result["score"].as<string>() + "\n"), 
				configs::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		}
	} else {
		configs::MyLog::verbose_out(log, ("ERROR: No musicXML file found, please supply a "
			"musicXML file to process.\n"), configs::VERBOSE_LEVEL::VERBOSE_ERRORS);
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
	const NoteList note_list(score);

//---------------------- Instrument creation ----------------------------
	
	std::shared_ptr<ActionSet<Node_Tuple, Distance>> action_set;
	if (result.count("test")) {
		if (result["test"].as<int>() == 1) {
			action_set = configs::test_configuration_1();
		} else if (result["test"].as<int>() == 2) { 
			action_set = configs::test_configuration_2();
		}
	} else {
		action_set = configs::test_configuration_1();
	}

	Instrument<Node_Tuple, Distance> violin(action_set);
	violin.makeIString(1, Note::G_3, Note::Gs_5);
	violin.makeIString(2, Note::D_4, Note::Ds_6);
	violin.makeIString(3, Note::A_4, Note::As_6);
	violin.makeIString(4, Note::E_5, Note::F_7);

	std::shared_ptr<NoteMapper<Node_Tuple>> note_mapper(new BasicNoteMapper(violin.getStrings()));

//-------------------------- Graph building/solving -------------------------
	std::shared_ptr<GraphSolver<Node_Tuple, Distance>> solver;
	
	try {
		LayerList<Node_Tuple, Distance> list(note_list, note_mapper);
	 	list.buildTransitions(violin.getActionSet());
		
		if (result.count("greedy")) {
			solver = std::shared_ptr<GraphSolver<Node_Tuple, Distance>>(new GreedySolver());
		} else {
			configs::MyLog::verbose_out(log, 
					"Defaulting to greedysolver as no other solver is available.\n",
					configs::VERBOSE_LEVEL::VERBOSE_ALL);
			solver = std::shared_ptr<GraphSolver<Node_Tuple, Distance>>(new GreedySolver());
		}
		try {
			solver->solve(list);
		} catch (SolverException e) {
			configs::MyLog::verbose_out(log, e.what() + "\nFailed layer transition: " + 
				to_string(e.getCount()) + " -> " + to_string(e.getCount() + 1) + "\n", 
				configs::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		} catch (std::out_of_range e) {
			configs::MyLog::verbose_out(log, std::string(e.what()) + "\n", 
					configs::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		}
	}
	catch (NodeException<Node_Tuple> e) {
		configs::MyLog::verbose_out(log,
					    e.what() + "Failed note: " + e.failedNote().to_string() + "\n",
					    configs::VERBOSE_LEVEL::VERBOSE_ERRORS);
		return -1;
	} catch (LinkException<Node_Tuple, Distance> e) {
		configs::MyLog::verbose_out(log,
					    e.what(),
					    configs::VERBOSE_LEVEL::VERBOSE_ERRORS);
		return -1;
	}



//------------------------------ Output ----------------------------------
	if (result.count("output")) {
		auto out_file = result["output"].as<std::string>();
		ofstream out;
		out.open(out_file, std::ofstream::binary);
		if (!out.is_open()) {
			configs::MyLog::verbose_out(log, "Failed to open file: " + out_file + 
				", Aborting...\n", configs::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		}
		configs::writeOutput(out, solver, result["csv"].as<bool>());
		out.close();
	} else {
		ostream out(std::cout.rdbuf());
		configs::writeOutput(out, solver, result["csv"].as<bool>());
	}
	return 0;
}
