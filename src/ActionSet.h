#ifndef ACTION_SET_H_MFPG
#define ACTION_SET_H_MFPG

#include "Action.h"
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <map>

//Class for a set of actions to be considered when calculating the transition between
//two states, each action is considered individually for the state transition but 
//is only executed if there are no dependencies preventing it from doing so (as 
//defined by the user).
template <class InputTuple, OutputViable OutputValue> class ActionSet {
	private:
		//Actions with their respective default running configuration, 
		//false = do not run by default, true = run by default.
		std::vector<std::tuple<Action<InputTuple, OutputValue>, bool>> actions;

		//Multimap of dependencies, the key is the dependent, the values
		//are the dependency actions with the boolean adjustment as a tuple.
		//For Example: "action1", {"action2", true} says that if action2 
		//occurred then action1 should occur.
		std::multimap<std::string, std::tuple<std::string, bool>> dependencies;

		//Check whether an action is to be taken or not with respect to the
		//dependencies in the dependencies multimap, the default action in the 
		//action set, and with the previous actions already taken.
		bool checkAction(std::string action_name, bool _default, 
					std::vector<std::string> previous_actions) {
			std::vector<bool> bools;
			//for loop Iterates through each dependency for the action to 
			//be performed.
			for (auto [dep_itr, range_end] = 
				   dependencies.equal_range(action_name); 
				   dep_itr != range_end; dep_itr++) {
				//For each dependency, check whether the depended 
				//action has occured in the previousActions list.
				if (find(previous_actions.begin(),
					      previous_actions.end(),
					      std::get<0>(dep_itr->second)) !=
					      previous_actions.end()) {

					//If the depended action has occured, add the 
					//boolean adjustment to the list of bools to be
					//checked later.
					bools.push_back(std::get<1>(dep_itr->second));
				}
			}
			bool ret = _default;
			for (bool b : bools) {
				//if _default is true, check conjunction with 
				//dependencies, otherwise check disjunction
				if (_default) {
					ret = ret && b;
				} else {
					ret = ret || b;
				}
			}
			return ret;
		}	
	public:
		ActionSet() {};
		ActionSet(std::vector<std::tuple<Action<InputTuple, OutputValue>, 
				bool>> as) : actions(as) {}
		ActionSet(Action<InputTuple, OutputValue> a, bool b) {
			addAction(a, b);
		}
		ActionSet(std::initializer_list<std::tuple<Action<InputTuple, 
							OutputValue>, bool>> as) {
			for (auto a : as) {
				actions.push_back(a);
			}
		}	

		void addAction(Action<InputTuple, OutputValue> a, bool b) {
			std::tuple<Action<InputTuple, OutputValue>, bool> t(a, b);
			actions.push_back(t);
		}
		void addDependency(std::string dependent, std::string dependency, 
								bool adjustment) {
			std::tuple<std::string, bool> dep = {dependency, adjustment};
			dependencies.insert({dependent, dep});
		}	
	
		//Applies the actionset to two tuples; n1 to n2.	
		OutputValue apply(InputTuple n1, InputTuple n2) {
			OutputValue output = {}; //output must be zero-initializable
			std::vector<std::string> taken = {};
			//For each action, check whether it should run, then calculate
			//distance to cumulatively add to the output.
			for (std::tuple<Action<InputTuple, OutputValue>, bool> a : 
									actions) 
			{
				if (checkAction(std::get<0>(a).getID(), 
				   std::get<1>(a),taken) 
				   && std::get<0>(a).condition(n1, n2))
				{
					output = output + 
						    std::get<0>(a).distance(n1, n2);
					taken.push_back(std::get<0>(a).getID());
				}	
			}
			return output;	
		}
		std::vector<std::tuple<Action<InputTuple, OutputValue>, bool>>
								getActions() {
				return actions;
		}
		std::multimap<std::string, std::tuple<std::string, bool>> 
								getDependencies() {
			return dependencies;
		}
};
#endif
