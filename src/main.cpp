#include "mx/api/ScoreData.h"
#include "mx/api/DocumentManager.h"

#include "cxxopts.hpp"

#include "conf_cmake.h"
#include "Log.h"
#include "configs.h"

#include "NoteEnums.h"
#include "NoteMapper.h"
#include "BasicNoteMapper.h"
#include "CSVNoteMapper.h"
#include "ActionSet.h"
#include "LayerList.h"
#include "NoteList.h"
#include "GraphSolver.h"
#include "GreedySolver.h"
#include "Instrument.h"
#include "PhysAttrMap.h"
#include "ExValException.h"
#include "SPSolver.h"
#include "InstrumentBuilder.h"
#include "NoteMapperException.h"

#include "ParserError.H"
#include "Parser.H"

#include <iostream>
#include <cstdio>
#include <fstream>
#include <memory>
#include <string>

using namespace noteenums;
using namespace std;

//TODO Add double outputs 
using Distance = int;

//Global variables used for synchronization and correctness checks
extern int TUPLESIZE;
extern std::string ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

int main (int argc, char *argv[]) {
//-------------------------------- Input/Arguments -------------------------
	cxxopts::Options options("mfpg");
	options.positional_help("[optional args]").show_positional_help();
	options.add_options()
		("score", "Input file in musicXML format.", cxxopts::value<std::string>())
		("version", "Shows program version.")
		("greedy", "Use GreedySolver instead of standard solver, for testing.")
		("shortest-path", "Use shortest path solver with optional optimizing levels (0, 1, 2).", cxxopts::value<int>()->implicit_value("0"))
		("n,notemapper", "Select which notemapper to use.", cxxopts::value<std::string>())
		("h,help", "Show this message.")
		("c,csv", "Structure output as CSV.")
		("t,test", "Select test parameters (1, 2).", cxxopts::value<int>())
		("v,verbose", "Make output more verbose (0, 1, 2).", cxxopts::value<int>())
		("o,output", "Specify where the output should be written.",cxxopts::value<std::string>())
		("d,dsl", "Use the DSL to specify strings, actions and attributes.", cxxopts::value<std::string>())
		("interactive", "For interactive testing of layers.");
	options.parse_positional({"score"});

	ostream& log = std::cout;

	auto result = options.parse(argc, argv);

	if (result.count("help")) {
		std::cout << options.help() << "\n";
		return 0;
	}

	if (result.count("version")) {
		std::cout << "mfpg version: " << VERSION_MFPG << "\n";
		return 0;
	}

	if (result.count("verbose")) {
		mfpg_log::VERBOSE = static_cast<mfpg_log::VERBOSE_LEVEL>(result["verbose"].as<int>());
		mfpg_log::Log::verbose_out(log, "Verbose option set: " + 
				(to_string(result["verbose"].as<int>())) + "\n", 
				mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
	}

//-------------------------- Read Score ---------------------------------

	string score_path;
	if (result.count("score")) {
		score_path = result["score"].as<std::string>();
		ifstream input_file;
		input_file.open(score_path);
		if (!input_file.is_open()) {
			mfpg_log::Log::verbose_out(log, ("ERROR: Could not open file: " + 
				result["score"].as<string>() + "\n"), 
				mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		}
		input_file.close();
	} else {
		mfpg_log::Log::verbose_out(log, ("ERROR: No musicXML file found, please supply a "
			"musicXML file to process.\n"), mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
		return -1;
	}


//------------------------- MX conversion --------------------------------

	using namespace mx::api;
	auto& mgr = DocumentManager::getInstance();
	const auto documentID = mgr.createFromFile(score_path);
	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	const NoteList note_list(score);

//---------------------- Instrument creation ----------------------------
	//Patchwork solution until fixed output typing.	
	std::shared_ptr<Instrument<int>> violin_i;
	std::shared_ptr<Instrument<double>> violin_d;

	//If the DSL is used.
	if (result.count("dsl")) {
		char output = 'i';
		InstrumentBuilder instrument_builder;

		//------- Parse DSL file -----------
		FILE *dsl_file;
		auto dsl_path = result["dsl"].as<std::string>();
		dsl_file = fopen(dsl_path.c_str(), "r");
		
		if (!dsl_file) {
			mfpg_log::Log::verbose_out(log, ("ERROR: Could not open file: " + 
				result["dsl"].as<string>() + "\n"), 
				mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		}
		
		Input *parse_tree = NULL;
		
		try {
			parse_tree = pInput(dsl_file);
		//Exception for if a parser fails to parse the DSL file.
		} catch( parse_error &e) {
			mfpg_log::Log::verbose_out(log, 
				("ERROR: Could not parse DSL file: " + result["dsl"].as<string>() 
				 	+ "\nParse error on line: " + to_string(e.getLine())), 
				mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
		}
		fclose(dsl_file);

		instrument_builder.visitInput(parse_tree);

		//------- Collect outputs from builder --------

		output = instrument_builder.output;

		if (output == 'i') {
			violin_i = instrument_builder.i_inst;
		} else if (output == 'd') {
			violin_d = instrument_builder.d_inst;
		}
		
		TUPLESIZE = instrument_builder.attrs.size();
		ATTRIBUTES = instrument_builder.attrs;
		ATTRIBUTE_TYPES = instrument_builder.attrtypes;

	//If the DSL is not used and test-configuration is used
	} else if (result.count("test")) {
		std::shared_ptr<ActionSet<int>> action_set(new ActionSet<int>());
		if (result["test"].as<int>() == 1) {
			action_set = configs::test_configuration_1();
		} else if (result["test"].as<int>() == 2) {
			action_set = configs::test_configuration_2();
		} else {
			action_set = configs::test_configuration_1();
		}
		std::shared_ptr<Instrument<int>> tmp_v(new Instrument<int>(action_set));
		tmp_v->makeIString(1, Note::G_3, Note::Gs_5);
		tmp_v->makeIString(2, Note::D_4, Note::Ds_6);
		tmp_v->makeIString(3, Note::A_4, Note::As_6);
		tmp_v->makeIString(4, Note::E_5, Note::F_7);

		violin_i = tmp_v;
		
		TUPLESIZE = 3;
		ATTRIBUTE_TYPES = "iii";
		ATTRIBUTES = {"STRING", "FINGER", "HAND_POS"};

	//Otherwise no instrument was defined.
	} else {
		mfpg_log::Log::verbose_out(std::cout,
			    "No Instrument was defined, Aborting...\n",
			    mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS
			    );
		return -1;
	}

//-------------------------- Graph building/solving -------------------------
	std::shared_ptr<NoteMapper> note_mapper;
	//if notemapper is used then an outside CSV notemapper file is used.
	if (result.count("notemapper")) {
		std::string map_csv_path = result["notemapper"].as<std::string>();
		try {
			note_mapper = std::shared_ptr<NoteMapper>(new CSVNoteMapper(map_csv_path, violin_i->getIStrings()));
		//If the notemapper cannot parse the CSV file/if the CSV file does not contain the correct
		//attributes.
		} catch (NoteMapperException e) {
			mfpg_log::Log::verbose_out(log, 
				e.what(), 
				mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
		}
	} else {
		note_mapper = std::shared_ptr<NoteMapper>(new BasicNoteMapper(violin_i->getIStrings()));
	}

	//TODO fix distance solver.
	//TODO Fix opt levels and documentation.
	//TODO catch exceptions as refs
	std::shared_ptr<GraphSolver<Distance>> solver;
	try {
		//Build the layerlist from the notelist and mapper.
		LayerList<Distance> list(note_list, note_mapper);

		//Build transitions between layers using the ActionSet
	 	list.buildTransitions(violin_i->getActionSet());
		
		//Interactive mode allows to explore the graph interactively, very basic, used for testing.
		if (result.count("interactive")) {
			int row, column;
			char cont;
			while (true) {
				std::cout << "Select which layer you want to view.\n";
				std::cin >> row;
				if (row < list.getSize() && row >= 0) {
					std::cout << "Layer " << row << " selected, size (from 0): " 
						  << list.getList(row).getElem().getSize() - 1 << "\n";
					std::cout << "Select which physmap you want to view.\n";
					std::cin >> column;
					if (column < list.getList(row).getElem().getSize() && column >= 0) {
						std::cout << "Transitions for physmap: " << list.getList(row)
											.getElem()
											.getNodes()[column]
											.to_string_csv() 
						  << " Note: " << list.getList(row).getElem().getNote() 
						  << "\n";
						std::cout << "Elems:      | ";
						for (int i = 0; i < list.getList(row)
									.getTransitions()[column]
									.size(); i++) {
							std::cout << i << " | ";
						}
						std::cout << "\n";
						std::cout << "Costs:      | ";
						for (int i = 0; i < list.getList(row)
									.getTransitions()[column]
									.size(); i++) {
							std::cout << list.getList(row)
									.getTransitions()
									[column][i] << " | ";
						}
						while (true) {
						std::cout << "\nContinue? [y/n]\n";
						std::cin >> cont;
							if (cont == 'n') {
								return 1;
							} else if (cont == 'y') {
								break;
							} else {
								std::cout << "Character not recognized.";
							}
						}
					} else {
						std::cout << "Physmap index out of bounds, try again.\n\n";
					}
				} else {
					std::cout << "LayerList index out of bounds, try again.\n";
				}
			}
		}

		//Select solver
		if (result.count("greedy")) {
			solver = std::shared_ptr<GraphSolver<Distance>>(new GreedySolver());
			mfpg_log::Log::verbose_out(log, 
					"Using Greedy solver\n",
					mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
		} else if (result.count("shortest-path")) {
			int opt = result["shortest-path"].as<int>();
			mfpg_log::Log::verbose_out(log, 
					"Using Shortest Path solver with optimizing level: " + to_string(opt) + "\n",
					mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
			solver = std::shared_ptr<GraphSolver<Distance>>(new SPSolver<int>(opt));
		} else {
			mfpg_log::Log::verbose_out(log, 
					"No solver selected, defaulting to Shortest Path solver with optimizing level 1\n",
					mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
			solver = std::shared_ptr<GraphSolver<Distance>>(new SPSolver<int>(2));
		} 
		solver->solve(list);
//------------------------------ Output ----------------------------------
		if (result.count("output")) {
			auto out_file = result["output"].as<std::string>();
			ofstream out;
			out.open(out_file, std::ofstream::binary);
			if (!out.is_open()) {
				mfpg_log::Log::verbose_out(log, "Failed to open file: " + out_file + 
					", Aborting...\n", mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
				return -1;
			}
			configs::writeOutput(out, solver, result["csv"].as<bool>());
			out.close();
		} else {
			ostream out(std::cout.rdbuf());
			configs::writeOutput(out, solver, result["csv"].as<bool>());
		}
		return 1;
	}
	//Exception for if adding nodes to layers fail.
	catch (NodeException e) {
		mfpg_log::Log::verbose_out(log,
					    e.what() + "Failed note: " + e.failedNote().to_string() + 
					    " Failed node: " + e.failedNode().to_string() + "\n",
					    mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
		return -1;
	//Exception for if there is a problem linking layers together.
	} catch (LinkException<Distance> e) {
		mfpg_log::Log::verbose_out(log,
					    e.what(),
					    mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
		return -1;
	
	//Exception for failures of creating or accessing exclusive values from the physical representation
	//maps.
	} catch (ExValException e) {
		std::string affected_tuples = "[";
		int count = 1;
		for (auto t : e.getExVal()) {
			affected_tuples += "Tuple " + std::to_string(count) + ": " + t.to_string();
			if (count < e.getExVal().size()) {
				affected_tuples += ", ";
			} else {
				affected_tuples += "]";
			}
			count++;
		}
		mfpg_log::Log::verbose_out(log,
					    e.what() + "\nAffected Tuples: " + affected_tuples + "\n",
					    mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
	} catch (SolverException e) {
			mfpg_log::Log::verbose_out(log, e.what() + "\nFailed to find layer path: " + 
				to_string(e.getLayer()) + " -> " + to_string(e.getLayer() + 1) + "\n", 
				mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		//Exception for if access to layer nodes is out of range
		} catch (std::out_of_range e) {
			mfpg_log::Log::verbose_out(log, std::string(e.what()) + "\n", 
					mfpg_log::VERBOSE_LEVEL::VERBOSE_ERRORS);
			return -1;
		}


}
