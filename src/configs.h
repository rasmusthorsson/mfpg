#ifndef CONFIGS_MFPG_H
#define CONFIGS_MFPG_H

#include "GraphSolver.h"
#include "ActionSet.h"
#include "Log.h"

#include <ostream>
#include <memory>
#include <string>

using Distance = int;

int TUPLESIZE;
std::string ATTRIBUTE_TYPES;
std::vector<std::string> ATTRIBUTES;

namespace configs {
	using namespace std;
	
	void writeOutput(ostream& out, shared_ptr<GraphSolver<double>> solver, bool csv) {
		int count = 1;
		double total_cost = 0;
		if (csv) {
			out << "note number, note, string, finger, hp, cost, "
				"combinations\r\n";
			for (auto sol : solver->getSolution()) {
				out << count << ","
					<< get<0>(sol).getNote() << ","
					<< get<0>(sol).getState().to_string_csv()
					<< get<1>(sol) << ","
					<< get<0>(sol).getLayerList().getElem().getSize() 
					<< "\r\n";
				count++;
				if (get<1>(sol) > -1) {
					total_cost += get<1>(sol);
				}
			}
		} else {
			for (auto sol : solver->getSolution()) {
				out << "Note number: " << count << "\n";
				out << "Note: " << get<0>(sol).getNote() << "\n";
				out 
					<< get<0>(sol).getState().to_string() 
					<< "\n"
					<< "Distance of transition: " << get<1>(sol) 
					<< "\n"
					<< "Amount of possible fingerings: " 
					<< get<0>(sol).getLayerList().getElem().getSize() 
					<< "\n"
					<< "------------------------------------" 
					<< "\n";
				count++;
				if (get<1>(sol) > -1) {
					total_cost += get<1>(sol);
				}
			}
		}
		mfpg_log::Log::verbose_out(std::cout,
				   "Total cost of the path: " + to_string(total_cost) + "\n",
				   mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
	}

	void writeOutput(ostream& out, shared_ptr<GraphSolver<int>> solver, bool csv) {
		int count = 1;
		int total_cost = 0;
		if (csv) {
			out << "note number, note, string, finger, hp, cost, "
				"combinations\r\n";
			for (auto sol : solver->getSolution()) {
				out << count << ","
					<< get<0>(sol).getNote() << ","
					<< get<0>(sol).getState().to_string_csv()
					<< get<1>(sol) << ","
					<< get<0>(sol).getLayerList().getElem().getSize() 
					<< "\r\n";
				count++;
				if (get<1>(sol) > -1) {
					total_cost += get<1>(sol);
				}
			}
		} else {
			for (auto sol : solver->getSolution()) {
				out << "Note number: " << count << "\n";
				out << "Note: " << get<0>(sol).getNote() << "\n";
				out 
					<< get<0>(sol).getState().to_string() 
					<< "\n"
					<< "Distance of transition: " << get<1>(sol) 
					<< "\n"
					<< "Amount of possible fingerings: " 
					<< get<0>(sol).getLayerList().getElem().getSize() 
					<< "\n"
					<< "------------------------------------" 
					<< "\n";
				count++;
				if (get<1>(sol) > -1) {
					total_cost += get<1>(sol);
				}
			}
		}
		mfpg_log::Log::verbose_out(std::cout,
				   "Total cost of the path: " + to_string(total_cost) + "\n",
				   mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL);
	}
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
