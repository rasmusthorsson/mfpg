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
