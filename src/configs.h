#include "GraphSolver.h"
#include "ActionSet.h"

#include <ostream>
#include <memory>
#include <string>

using Node_Tuple = std::tuple<int, int, int>;
using Distance = int;

namespace configs {
	using namespace std;
	
	enum class VERBOSE_LEVEL {
		VERBOSE_NONE = 0,
		VERBOSE_ERRORS = 1,
		VERBOSE_ALL = 2
	};
	
	static VERBOSE_LEVEL VERBOSE = configs::VERBOSE_LEVEL::VERBOSE_ERRORS;

	class MyLog {
		public:
			MyLog() = delete;
			static void verbose_out(ostream& out, std::string s, VERBOSE_LEVEL v) {
				if (v <= VERBOSE) {
					out << s;
				}
			}	
	};

	void writeOutput(ostream& out, shared_ptr<GraphSolver<Node_Tuple, Distance>> solver, bool csv) {
		int count = 1;
		if (csv) {
			out << "note number, note, string, finger, hp, cost, "
				"combinations\r\n";
			for (auto sol : solver->getSolution()) {
				out << count << ","
					<< get<0>(sol).getNote() << ","
					<< get<0>(get<0>(sol).getState()) << ","
					<< get<2>(get<0>(sol).getState()) << ","
					<< get<1>(get<0>(sol).getState()) << ","
					<< get<1>(sol) << ","
					<< get<0>(sol).getLayerList().getSize() 
					<< "\r\n";
				count++;
			}
		} else {
			for (auto sol : solver->getSolution()) {
				out << "Note number: " << count << "\n";
				out << "Note: " << get<0>(sol).getNote() << "\n";
				out << "String: " << get<0>(get<0>(sol).getState())
					<< ", Finger: " 
					<< get<2>(get<0>(sol).getState())
					<< ", Hand Position: " 
					<< get<1>(get<0>(sol).getState()) << "\n"
					<< "Distance of transition: " << get<1>(sol) 
					<< "\n"
					<< "Amount of possible fingerings: " 
					<< get<0>(sol).getLayerList().getSize() 
					<< "\n"
					<< "------------------------------------" 
					<< "\n";
				count++;
			}
		}
	}
	shared_ptr<ActionSet<Node_Tuple, Distance>> test_configuration_2() {
		typedef Distance (*a_t_d) (Node_Tuple, Node_Tuple);
		typedef bool (*a_t_c) (Node_Tuple, Node_Tuple);

		a_t_c rest_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (t1 == Node_Tuple{0, 0, 0} || 
				t2 == Node_Tuple{0, 0, 0});
		};
		a_t_d rest_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 0;
		};

		a_t_c f_a_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (0 != (get<2>(t1) - get<2>(t2)));
		};
		a_t_d f_a_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 1;
		};

		a_t_c s_a_cross_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (2 <= (abs(get<0>(t1) - get<0>(t2))));
		};
		a_t_d s_a_cross_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 10;
		};

		a_t_c s_a_no_cross_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (0 != (get<0>(t1) - get<0>(t2)));
		};
		a_t_d s_a_no_cross_d = [](Node_Tuple t1, Node_Tuple t2) {
			return (abs(get<0>(t1) - get<0>(t2)));
		};

		a_t_c hp_a_no_change_c = [](Node_Tuple t1, Node_Tuple t2) {
			return(0 == (get<1>(t1) - get<1>(t2)));
		};
		a_t_d hp_a_no_change_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 0;
		};

		a_t_c hp_a_short_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (3 >= (abs(get<1>(t1) - get<1>(t2))));
		};
		a_t_d hp_a_short_d = [](Node_Tuple t1, Node_Tuple t2) {
			return (abs(get<1>(t1) - get<1>(t2)) + 1);
		};

		a_t_c hp_a_long_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (3 < (abs(get<1>(t1) - get<1>(t2))));
		};
		a_t_d hp_a_long_d = [](Node_Tuple t1, Node_Tuple t2) {
			return (2 * (abs(get<1>(t1) - get<1>(t2))));
		};

		a_t_c hp_a_high_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (5 < get<1>(t2));
		};
		a_t_d hp_a_high_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 5;
		};
		
		shared_ptr<ActionSet<Node_Tuple, Distance>> 
					action_set(new ActionSet<Node_Tuple, Distance>());
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
	shared_ptr<ActionSet<Node_Tuple, Distance>> test_configuration_1() {
		typedef Distance (*action_type_dist) (Node_Tuple, Node_Tuple);
		typedef bool (*action_type_cond) (Node_Tuple, Node_Tuple);

		action_type_cond hp_action_cond = [] (Node_Tuple t1, Node_Tuple t2) {
			return (0 != (get<1>(t1) - get<1>(t2)));
		};
		action_type_dist hp_action_dist = [] (Node_Tuple t1, Node_Tuple t2) {
			return abs(get<1>(t1) - get<1>(t2));
		};

		action_type_cond finger_action_cond = [] (Node_Tuple t1, Node_Tuple t2) {
			return (0 != (get<2>(t1) - get<2>(t2)));
		};
		action_type_dist finger_action_dist = [] (Node_Tuple t1, Node_Tuple t2) {
			return abs(get<2>(t1) - get<2>(t2));
		};

		action_type_cond string_action_NR_cond = [] (Node_Tuple t1, Node_Tuple t2) {
			return (2 <= (abs(get<0>(t1) - get<0>(t2))));
		};
		action_type_dist string_action_NR_dist = [] (Node_Tuple t1, Node_Tuple t2) {
			return (abs(get<0>(t1) - get<0>(t2)) + 100);
		};

		action_type_cond string_action_cond = [] (Node_Tuple t1, Node_Tuple t2) {
			return (0 < (abs(get<0>(t1) - get<0>(t2))));
		};
		action_type_dist string_action_dist = [] (Node_Tuple t1, Node_Tuple t2) {
			return (abs(get<0>(t1) - get<0>(t2)));
		};

		action_type_cond rest_cond = [] (Node_Tuple t1, Node_Tuple t2) {
			return (t1 == Node_Tuple{0, 0, 0} || t2 == Node_Tuple{0, 0, 0});
		};
		action_type_dist rest_dist = [] (Node_Tuple t1, Node_Tuple t2) {
			return 0;
		};

		shared_ptr<ActionSet<Node_Tuple, Distance>> action_set(
					new ActionSet<Node_Tuple, Distance> ());

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
