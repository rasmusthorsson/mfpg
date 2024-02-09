#include "GraphSolver.h"
#include "ActionSet.h"

#include "iostream"
#include "ostream"
#include "fstream"

using Node_Tuple = std::tuple<int, int, int>;
using Distance = int;

namespace configs {
	using namespace std;
	void writeOutput(ostream& out, GraphSolver<Node_Tuple, Distance>* solver, 
									bool csv) {
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
				    << "Distance of transition: " << get<1>(sol) 
				    << "\n"
				    << "Amount of possible fingerings: " 
				    << get<0>(sol).getLayerList().getSize() << "\n"
				    << "------------------------------------" << "\n";
				count++;
			}
		}
	}
	ActionSet<Node_Tuple, Distance> test_configuration_2() {
		typedef Distance (*a_t_d) (Node_Tuple, Node_Tuple);
		typedef bool (*a_t_c) (Node_Tuple, Node_Tuple);

		a_t_c rest_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (t1 == Node_Tuple{0, 0, 0} || t2 == Node_Tuple{0, 0, 0});
		};
		a_t_d rest_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 0;
		};
		Action<Node_Tuple, Distance> rest(rest_c, rest_d, "rest");

		a_t_c f_a_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (0 != (get<2>(t1) - get<2>(t2)));
		};
		a_t_d f_a_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 1;
		};
		Action<Node_Tuple, Distance> f_a(f_a_c, f_a_d, "f_a");

		a_t_c s_a_cross_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (2 <= (abs(get<0>(t1) - get<0>(t2))));
		};
		a_t_d s_a_cross_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 10;
		};
		Action<Node_Tuple, Distance> s_a_cross(s_a_cross_c, s_a_cross_d, "s_a_cross");

		a_t_c s_a_no_cross_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (0 != (get<0>(t1) - get<0>(t2)));
		};
		a_t_d s_a_no_cross_d = [](Node_Tuple t1, Node_Tuple t2) {
			return (abs(get<0>(t1) - get<0>(t2)));
		};
		Action<Node_Tuple, Distance> s_a_no_cross(s_a_no_cross_c, s_a_no_cross_d, "s_a_no_cross");

		a_t_c hp_a_short_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (3 >= (abs(get<1>(t1) - get<1>(t2))));
		};
		a_t_d hp_a_short_d = [](Node_Tuple t1, Node_Tuple t2) {
			return (abs(get<1>(t1) - get<1>(t2)));
		};
		Action<Node_Tuple, Distance> hp_a_short(hp_a_short_c, hp_a_short_d, "hp_a_short");
		
		a_t_c hp_a_long_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (3 < (abs(get<1>(t1) - get<1>(t2))));
		};
		a_t_d hp_a_long_d = [](Node_Tuple t1, Node_Tuple t2) {
			return (3 * (abs(get<1>(t1) - get<1>(t2))));
		};
		Action<Node_Tuple, Distance> hp_a_long(hp_a_long_c, hp_a_long_d, "hp_a_long");

		a_t_c hp_a_high_c = [](Node_Tuple t1, Node_Tuple t2) {
			return (5 < get<1>(t2));
		};
		a_t_d hp_a_high_d = [](Node_Tuple t1, Node_Tuple t2) {
			return 5;
		};
		Action<Node_Tuple, Distance> hp_a_high(hp_a_high_c, hp_a_high_d, "hp_a_high");

		ActionSet<Node_Tuple, Distance> action_set({
							  {rest, true},
							  {f_a, true},
							  {s_a_cross, true},
							  {s_a_no_cross, true},
							  {hp_a_short, true},
							  {hp_a_long, true},
							  {hp_a_high, true}
							  });
		
		action_set.addDependency("f_a", "rest", false);
		action_set.addDependency("s_a_cross", "rest", false);
		action_set.addDependency("s_a_no_cross", "rest", false);
		action_set.addDependency("hp_a_short", "rest", false);
		action_set.addDependency("hp_a_long", "rest", false);
		action_set.addDependency("s_a_no_cross", "s_a_cross", false);

		return action_set;
	}
	ActionSet<Node_Tuple, Distance> test_configuration_1() {
		typedef Distance (*action_type_dist) (Node_Tuple, Node_Tuple);
		typedef bool (*action_type_cond) (Node_Tuple, Node_Tuple);
		
		action_type_cond hp_action_cond = [] (Node_Tuple t1, Node_Tuple t2) {
			return (0 != (get<1>(t1) - get<1>(t2)));
		};
		action_type_dist hp_action_dist = [] (Node_Tuple t1, Node_Tuple t2) {
			return abs(get<1>(t1) - get<1>(t2));
		};
		Action<Node_Tuple, Distance> hp_action(hp_action_cond, 
						     hp_action_dist, 
						     "hp_action");

		action_type_cond finger_action_cond = [] (Node_Tuple t1, 
								Node_Tuple t2) {
			return (0 != (get<2>(t1) - get<2>(t2)));
		};
		action_type_dist finger_action_dist = [] (Node_Tuple t1, 
								Node_Tuple t2) {
			return abs(get<2>(t1) - get<2>(t2));
		};
		Action<Node_Tuple, Distance> finger_action(finger_action_cond, 
						     finger_action_dist, 
						     "finger_action");

		action_type_cond string_action_NR_cond = [] (Node_Tuple t1, 
								Node_Tuple t2) {
			return (2 <= (abs(get<0>(t1) - get<0>(t2))));
		};
		action_type_dist string_action_NR_dist = [] (Node_Tuple t1, 
								Node_Tuple t2) {
			return (abs(get<0>(t1) - get<0>(t2)) + 100);
		};
		Action<Node_Tuple, Distance> string_action_NR(string_action_NR_cond, 
						     string_action_NR_dist, 
						     "string_action_NR");

		action_type_cond string_action_cond = [] (Node_Tuple t1, 
								Node_Tuple t2) {
			return (0 < (abs(get<0>(t1) - get<0>(t2))));
		};
		action_type_dist string_action_dist = [] (Node_Tuple t1, 
								Node_Tuple t2) {
			return (abs(get<0>(t1) - get<0>(t2)));
		};
		Action<Node_Tuple, Distance> string_action(string_action_cond, 
						     string_action_dist, 
						     "string_action");
		
		action_type_cond rest_cond = [] (Node_Tuple t1, Node_Tuple t2) {
			return (t1 == Node_Tuple{0, 0, 0} || 
					t2 == Node_Tuple{0, 0, 0});
		};
		action_type_dist rest_dist = [] (Node_Tuple t1, Node_Tuple t2) {
			return 0;
		};
		Action<Node_Tuple, Distance> rest(rest_cond, 
						  rest_dist, 
						  "rest");
		
		ActionSet<Node_Tuple, Distance> action_set({
							{rest, true},
							{hp_action, true},
							{finger_action, true},
							{string_action_NR, true},
							{string_action, true}
							});

		action_set.addDependency("hp_action", "rest", false);
		action_set.addDependency("finger_action", "rest", false);
		action_set.addDependency("string_action_NR", "rest", false);
		action_set.addDependency("string_action", "rest", false);
		action_set.addDependency("string_action", "string_action_NR", false);

		return action_set;
	}
};
