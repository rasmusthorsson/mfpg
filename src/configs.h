#ifndef CONFIGS_MFPG_H
#define CONFIGS_MFPG_H

#include "GraphSolver.h"
#include "ActionSet.h"
#include "Log.h"

#include <ostream>
#include <memory>
#include <string>
#include <set>

using Distance = int;

int TUPLESIZE;
std::string ATTRIBUTE_TYPES;
std::string INSTRUMENT_NAME;
std::vector<std::string> ATTRIBUTES;
std::set<std::string> DEFINITIVES;

namespace configs {
	using namespace std;
	
	enum OUTPUT_TYPE {
		BASIC,
		CSV,
		READABLE
	};
	
//------------------------------------- OUTPUT FUNCTIONS ------------------------------------------------
	template<class Output>
	void writeOutputBasic(ostream& out, shared_ptr<GraphSolver<Output>> solver, OUTPUT_TYPE output,
			set<string> columns) {
		int count = 1;
		int total_cost = 0;
		for (auto sol : solver->getSolution()) {
			out << "Note number: " << count << "\n";
			for (string def : DEFINITIVES) {
				if (def == "NOTE") {
					out << "Note: " << get<0>(sol).getNote().getNote() << "\n";
				} else if (def == "DURATION") {
					out << "Duration: " << get<0>(sol).getNote().getDuration() << "\n";
				}
			}
			out << get<0>(sol).getState().to_string() << "\n";
			out << "Cost of transition: " << get<1>(sol) << "\n";
			out << "Amount of possible fingerings: " 
				<< get<0>(sol).getLayerList().getElem().getSize() << "\n";
			out << "--------------------------------------------------" << "\n";
			count++;
			if (get<1>(sol) > -1) {
				total_cost += get<1>(sol);
			}
		}
		mfpg_log::Log::verbose_out(std::cout,
				   "Total cost of the path: " + to_string(total_cost) + "\n",
				   mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
	}

	template<class Output>
	void writeOutputCSV(ostream& out, shared_ptr<GraphSolver<Output>> solver, OUTPUT_TYPE output,
			set<string> columns) {
		bool not_first = false;
		int count = 1;
		int total_cost = 0;
		bool all = columns.size() == 0;
		//Headers
		if (columns.contains("NoteCount") || all) {
			if (not_first) out << ","; else not_first = true;
			out << "NoteCount";
		}
		for (string def : DEFINITIVES) {
			if (columns.contains(def) || all) {
				if (not_first) out << ","; else not_first = true;
				out << def;
			}
		}
		if (columns.contains("Cost") || all) {
			if (not_first) out << ","; else not_first = true;
			out << "Cost";
		}
		if (columns.contains("Combinations") || all) {
			if (not_first) out << ","; else not_first = true;
			out << "Combinations";
		}
		for (int i = 0; i < ATTRIBUTES.size(); i++) {
			if (columns.contains(ATTRIBUTES[i]) || all) {
				if (not_first) out << ","; else not_first = true;
				out << ATTRIBUTES[i];
			}
		}
		not_first = false;
		out << "\r\n";
		//Columns
		for (auto sol : solver->getSolution()) {
			if (columns.contains("NoteCount") || all) {
				if (not_first) out << ","; else not_first = true;
				out << count;
			}
			for (string def : DEFINITIVES) {
				if (def == "NOTE") {
					if (columns.contains("NOTE") || all) {
						if (not_first) out << ","; else not_first = true;
						out << get<0>(sol).getNote().getNote();
					}
				} else if (def == "DURATION") {
					if (columns.contains("DURATION") || all) {
						if (not_first) out << ","; else not_first = true;
						out << get<0>(sol).getNote().getDuration();
					}
				}
			}
			if (columns.contains("Cost") || all) {
				if (not_first) out << ","; else not_first = true;
				out << get<1>(sol);
			}
			if (columns.contains("Combinations") || all) {
				if (not_first) out << ","; else not_first = true;
				out << get<0>(sol).getLayerList().getElem().getSize();
			}
			for (int i = 0; i < ATTRIBUTES.size(); i++) {
				if (columns.contains(ATTRIBUTES[i]) || all) {
					if (not_first) out << ","; else not_first = true;
					out << get<0>(sol).getState().getVal(ATTRIBUTES[i])
						.to_string_csv();
				}
			}
			not_first = false;
			out << "\r\n";
			count++;
			if (get<1>(sol) > -1) {
				total_cost += get<1>(sol);
			}
		}
		mfpg_log::Log::verbose_out(std::cout,
				   "Total cost of the path: " + to_string(total_cost) + "\n",
				   mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
	}

	template<class Output>
	void writeOutputReadable(ostream& out, shared_ptr<GraphSolver<Output>> solver, OUTPUT_TYPE output,
			set<string> columns) {
		bool first = true;
		int count = 1;
		int total_cost = 0;
		bool all = columns.size() == 0;
		Output prev_cost = {};
		std::shared_ptr<HandPosition<Output>> current(
					new HandPosition<Output>(get<0>(solver->getSolution().front())));
		std::shared_ptr<HandPosition<Output>> prev(
					new HandPosition<Output>(get<0>(solver->getSolution().front())));
		for (auto sol : solver->getSolution()) {
			if (first) {
				for (string def : DEFINITIVES) {
					if (def == "NOTE" && (columns.contains("NOTE") || all)) {
						out << "First note to be played is: " << get<0>(sol)
							.getNote().getNote() << "\n";
						break;
					}
				}
				out << "\n";
				for (int i = 0; i < ATTRIBUTES.size(); i++) {
					if (columns.contains(ATTRIBUTES[i]) || all) {
						out << "Start " << ATTRIBUTES[i];
						out << " at ";
						out << get<0>(sol).getState()
						    .getVal(ATTRIBUTES[i]).to_string_csv();
						out << "\n";
					}
				}	
				out << "\n";
				if (columns.contains("Combinations") || all) {
					out << "There were ";
					out << get<0>(sol).getLayerList().getElem().getSize();
					out << " possible ways to start.\n";
				}
				out << "---------------------------------------------------\n";
				first = false;
			} else {
				if (current->getState() != get<0>(sol).getState()) {
					if (columns.contains("NoteCount") || all) {
						out << "Change of position for note number: "; 
						out << count;
						out << "\n";
					}
					for (string def : DEFINITIVES) {
						if (def == "NOTE" && (columns.contains("NOTE") || all)) {
							out << "Note goes from "; 
							out << prev->getNote().getNote();
							out << " to "; 
							out << get<0>(sol).getNote().getNote();
							out << "\n";
							break;
						}
					}
					out << "\n";
					for (int i = 0; i < ATTRIBUTES.size(); i++) {
						if (columns.contains(ATTRIBUTES[i]) || all) {
							if (current->getState().getVal(ATTRIBUTES[i]) !=
							    get<0>(sol).getState().getVal(ATTRIBUTES[i])) {
								out << "Change "; 
								out << ATTRIBUTES[i];
								out << " from ";
								out << current->getState()
								    .getVal(ATTRIBUTES[i]).to_string_csv();
								out << " to ";
								out << get<0>(sol).getState()
								    .getVal(ATTRIBUTES[i]).to_string_csv();
								out << "\n";
							} else {
								out << "Keep ";
								out << ATTRIBUTES[i];
								out << " "; 
								out << get<0>(sol).getState()
								    .getVal(ATTRIBUTES[i]).to_string_csv();
								out << "\n";
							}
						}
					}	
					out << "\n";
					if (columns.contains("Cost") || all) {
						out << "This transition costs: "; 
						out << prev_cost;
						out << "\n";
					}
					if (columns.contains("Combinations") || all) {
						out << "There were ";
						out << get<0>(sol).getLayerList().getElem().getSize();
						out << " possible transitions.\n";
					}
					out << "---------------------------------------------------\n";
					current = shared_ptr<HandPosition<Output>>(
								new HandPosition<Output>(get<0>(sol)));
				}
				prev = shared_ptr<HandPosition<Output>>(
						new HandPosition<Output>(get<0>(sol)));
				prev_cost = get<1>(sol);
			}
			if (get<1>(sol) > -1) {
				total_cost += get<1>(sol);
			}
			count++;
		}
		mfpg_log::Log::verbose_out(std::cout,
				   "Total cost of the path: " + to_string(total_cost) + "\n",
				   mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
	}
	template<class Output>
	void writeOutput(ostream& out, shared_ptr<GraphSolver<Output>> solver, OUTPUT_TYPE output,
			std::set<std::string> columns) {
		if (output == OUTPUT_TYPE::BASIC) {
			writeOutputBasic(out, solver, output, columns);
		} else if (output == OUTPUT_TYPE::CSV) {
			writeOutputCSV(out, solver, output, columns);
		} else if (output == OUTPUT_TYPE::READABLE) {
			writeOutputReadable(out, solver, output, columns);
		} else {
			return;
		}
	}
//------------------------------------- BUILT-IN TEST CONFIGURATIONS ---------------------------------------
	shared_ptr<ActionSet<Distance>> test_configuration_2() {
		typedef Distance (*a_t_d) (NoteAttributes, NoteAttributes);
		typedef bool (*a_t_c) (NoteAttributes, NoteAttributes);

		a_t_c rest_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (t1.getPhysAttr() == PhysAttrMap{0, 0, 0} || 
				t2.getPhysAttr() == PhysAttrMap{0, 0, 0});
		};
		a_t_d rest_d = [](NoteAttributes t1, NoteAttributes t2) {
			return 0;
		};
		a_t_c f_a_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (0 != int(t1.getPhysAttr().getVal("FINGER") - t2.getPhysAttr().getVal("FINGER")));
		};
		a_t_d f_a_d = [](NoteAttributes t1, NoteAttributes t2) {
			return 1;
		};

		a_t_c s_a_cross_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (2 <= abs(int(t1.getPhysAttr().getVal("STRING") - t2.getPhysAttr().getVal("STRING"))));
		};
		a_t_d s_a_cross_d = [](NoteAttributes t1, NoteAttributes t2) {
			return 10;
		};

		a_t_c s_a_no_cross_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (0 != int(t1.getPhysAttr().getVal("STRING") - t2.getPhysAttr().getVal("STRING")));
		};
		a_t_d s_a_no_cross_d = [](NoteAttributes t1, NoteAttributes t2) {
			return abs(int(t1.getPhysAttr().getVal("STRING") - t2.getPhysAttr().getVal("STRING")));
		};

		a_t_c hp_a_no_change_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (0 == int(t1.getPhysAttr().getVal("HAND_POS") - t2.getPhysAttr().getVal("HAND_POS")));
		};
		a_t_d hp_a_no_change_d = [](NoteAttributes t1, NoteAttributes t2) {
			return 0;
		};

		a_t_c hp_a_short_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (3 >= abs(int(t1.getPhysAttr().getVal("HAND_POS") - t2.getPhysAttr().getVal("HAND_POS"))));
		};
		a_t_d hp_a_short_d = [](NoteAttributes t1, NoteAttributes t2) {
			return (abs(int(t1.getPhysAttr().getVal("HAND_POS") - t2.getPhysAttr().getVal("HAND_POS"))) + 1);
		};

		a_t_c hp_a_long_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (3 < abs(int(t1.getPhysAttr().getVal("HAND_POS") - t2.getPhysAttr().getVal("HAND_POS"))));
		};
		a_t_d hp_a_long_d = [](NoteAttributes t1, NoteAttributes t2) {
			return (2 * abs(int(t1.getPhysAttr().getVal("HAND_POS") - t2.getPhysAttr().getVal("HAND_POS"))));
		};

		a_t_c hp_a_high_c = [](NoteAttributes t1, NoteAttributes t2) {
			return (5 < t2.getPhysAttr().getVal("HAND_POS"));
		};
		a_t_d hp_a_high_d = [](NoteAttributes t1, NoteAttributes t2) {
			return 5;
		};
		
		shared_ptr<ActionSet<Distance>> action_set(new ActionSet<Distance>());
		action_set->makeAction(rest_c, rest_d, "rest", true);
		action_set->makeAction(f_a_c, f_a_d, "f_a", true);
		action_set->makeAction(s_a_cross_c, s_a_cross_d, "s_a_cross", true);
		action_set->makeAction(s_a_no_cross_c, s_a_no_cross_d, "s_a_no_cross", true);
		action_set->makeAction(hp_a_no_change_c, hp_a_no_change_d, "hp_a_no_change", true);
		action_set->makeAction(hp_a_short_c, hp_a_short_d, "hp_a_short", true);
		action_set->makeAction(hp_a_long_c, hp_a_long_d, "hp_a_long", true);
		action_set->makeAction(hp_a_high_c, hp_a_high_d, "hp_a_high", true);

		action_set->addDependency("f_a", "rest", false);
		action_set->addDependency("s_a_cross", "rest", false);
		action_set->addDependency("s_a_no_cross", "rest", false);
		action_set->addDependency("hp_a_short", "rest", false);
		action_set->addDependency("hp_a_long", "rest", false);
		action_set->addDependency("s_a_no_cross", "s_a_cross", false);
		action_set->addDependency("hp_a_short", "hp_a_no_change", false);

		return action_set;
	}
	shared_ptr<ActionSet<Distance>> test_configuration_1() {
		typedef Distance (*action_type_dist) (NoteAttributes, NoteAttributes);
		typedef bool (*action_type_cond) (NoteAttributes, NoteAttributes);

		action_type_cond hp_action_cond = [] (NoteAttributes t1, NoteAttributes t2) {
			return (0 != int(t1.getPhysAttr().getVal("HAND_POS") - t2.getPhysAttr().getVal("HAND_POS")));
		};
		action_type_dist hp_action_dist = [] (NoteAttributes t1, NoteAttributes t2) {
			return abs(int(t1.getPhysAttr().getVal("HAND_POS") - t2.getPhysAttr().getVal("HAND_POS")));
		};

		action_type_cond finger_action_cond = [] (NoteAttributes t1, NoteAttributes t2) {
			return (0 != int(t1.getPhysAttr().getVal("FINGER") - t2.getPhysAttr().getVal("FINGER")));
		};
		action_type_dist finger_action_dist = [] (NoteAttributes t1, NoteAttributes t2) {
			return abs(int(t1.getPhysAttr().getVal("FINGER") - t2.getPhysAttr().getVal("FINGER")));
		};

		action_type_cond string_action_NR_cond = [] (NoteAttributes t1, NoteAttributes t2) {
			return (2 <= abs(int(t1.getPhysAttr().getVal("STRING") - t2.getPhysAttr().getVal("STRING"))));
		};
		action_type_dist string_action_NR_dist = [] (NoteAttributes t1, NoteAttributes t2) {
			return abs(int(t1.getPhysAttr().getVal("STRING") - t2.getPhysAttr().getVal("STRING"))) + 100;
		};

		action_type_cond string_action_cond = [] (NoteAttributes t1, NoteAttributes t2) {
			return (0 < abs(int(t1.getPhysAttr().getVal("STRING") - t2.getPhysAttr().getVal("STRING"))));
		};
		action_type_dist string_action_dist = [] (NoteAttributes t1, NoteAttributes t2) {
			return abs(int(t1.getPhysAttr().getVal("STRING") - t2.getPhysAttr().getVal("STRING")));
		};

		action_type_cond rest_cond = [] (NoteAttributes t1, NoteAttributes t2) {
			return (t1.getPhysAttr() == PhysAttrMap{0, 0, 0} || t2.getPhysAttr() == PhysAttrMap{0, 0, 0});
		};
		action_type_dist rest_dist = [] (NoteAttributes t1, NoteAttributes t2) {
			return 0;
		};

		shared_ptr<ActionSet<Distance>> action_set(new ActionSet<Distance> ());

		action_set->makeAction(rest_cond, rest_dist, "rest", true);
		action_set->makeAction(hp_action_cond, hp_action_dist, "hp_action", true);
		action_set->makeAction(finger_action_cond, finger_action_dist, "finger_action", true);
		action_set->makeAction(string_action_NR_cond, string_action_NR_dist,
									"string_action_NR", true);
		action_set->makeAction(string_action_cond, string_action_dist, "string_action", true);

		action_set->addDependency("hp_action", "rest", false);
		action_set->addDependency("finger_action", "rest", false);
		action_set->addDependency("string_action_NR", "rest", false);
		action_set->addDependency("string_action", "rest", false);
		action_set->addDependency("string_action", "string_action_NR", false);

		return action_set;
	}
};
#endif
