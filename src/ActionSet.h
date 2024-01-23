#ifndef ACTION_SET_H_MFPG
#define ACTION_SET_H_MFPG

#include "Action.h"
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <map>

using namespace std;

//Class for a set of actions to be considered when calculating the transition between
//two states, each action is considered individually for the state transition but 
//is only executed if there are no dependencies preventing it from doing so (as 
//defined by the user).
template <class InputTuple, OutputViable OutputValue> class ActionSet {
	private:
		//Actions with their respective default running configuration, 
		//false = do not run by default, true = run by default.
		vector<tuple<Action<InputTuple, OutputValue>, bool>> actions;

		//Multimap of dependencies, the key is the dependency, the values
		//are the dependent actions with the boolean adjustment as a tuple.
		multimap<string, tuple<string, bool>> dependencies;

		//Check whether an action is to be taken or not with respect to the
		//dependencies in the dependencies multimap, the default action in the 
		//action set, and with the previous actions already taken.
		bool checkAction(string actionName, bool _default, 
					vector<string> previousActions) {
			vector<bool> bools;
			//for loop Iterates through each dependency for the action to 
			//be performed.
			for (auto depItr = dependencies.find(actionName); 
					depItr != dependencies.end();
					depItr++) {
				//For each dependency, check whether the depended 
				//action has occured in the previousActions list.
				if (find(previousActions.begin(),
					      previousActions.end(),
					      get<0>(depItr->second)) !=
					      previousActions.end()) {

					//If the depended action has occured, add the 
					//boolean adjustment to the list of bools to be
					//checked later.
					bools.push_back(get<1>(depItr->second));
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
		ActionSet(vector<tuple<Action<InputTuple, OutputValue>, 
				bool>> as) : actions(as) {}
		ActionSet(Action<InputTuple, OutputValue> a, bool b) {
			addAction(a, b);
		}
		ActionSet(initializer_list<tuple<Action<InputTuple, 
							OutputValue>, bool>> as) {
			for (auto a : as) {
				actions.push_back(a);
			}
		}	

		void addAction(Action<InputTuple, OutputValue> a, bool b) {
			tuple<Action<InputTuple, OutputValue>, bool> t(a, b);
			actions.push_back(t);
		}
		void addDependency(string dependent, string dependency, 
								bool adjustment) {
			tuple<string, bool> dep = {dependency, adjustment};
			dependencies.insert({dependent, dep});
		}	
	
		//Applies the actionset to two tuples; n1 to n2.	
		OutputValue apply(InputTuple n1, InputTuple n2) {
			OutputValue output = {}; //output must be zero-initializable
			vector<string> taken = {};
			//For each action, check whether it should run, then calculate
			//distance to cumulatively add to the output.
			for (tuple<Action<InputTuple, OutputValue>, bool> a : actions) 
			{
				if (checkAction(get<0>(a).getID(), get<1>(a), taken) 
				  && get<0>(get<0>(a).distance(n1, n2))) 
				{
					output = output + get<1>(get<0>(a)
								.distance(n1, n2));
					taken.push_back(get<0>(a).getID());
				}	
			}
			return output;	
		}
		vector<tuple<Action<InputTuple, OutputValue>, bool>>
								getActions() {
				return actions;
		}
		multimap<string, tuple<string, bool>> 
								getDependencies() {
			return dependencies;
		}
};
#endif
