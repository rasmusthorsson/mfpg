#include "Action.h"
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <map>
template <class InputTuple, OutputViable OutputValue> 
class ActionSet {
	private:
		//Actions with the default running configuration, false = do not run by
		//default, true = run by default.
		std::vector<std::tuple<Action<InputTuple, OutputValue>, bool>> actions;

		//Multimap of dependencies, the key is the dependant action, the values
		//are the depended actions with the boolean adjustment as a tuple.
		std::multimap<std::string, std::tuple<std::string, bool>> dependencies;

		//Check whether an action is to be taken or not with respect to the
		//dependencies in the dependencies multimap, the default action in the 
		//action set, and with the previous actions already taken.
		bool checkAction(std::string actionName, bool _default, 
				std::vector<std::string> previousActions) {
			std::vector<bool> bools;
			//For lop iterates through each dependency for the action to be
			//performed.
			for (auto dep_itr = dependencies.find(actionName); 
					dep_itr != dependencies.end();
					dep_itr++) {
				//For each dependency, check whether the depended action
				//has occured in the previousActions list.
				if (std::find(previousActions.begin(),
					      previousActions.end(),
					      std::get<0>(dep_itr->second)) !=
					      previousActions.end()) {
					//If the depended action has occured, add the 
					//boolean adjustment to the list of bools to be
					//checked later.
					bools.push_back(std::get<1>(dep_itr->second));
				}
			}
			bool ret = _default;
			for (bool b : bools) {
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
		ActionSet(std::initializer_list
				<std::tuple<Action<InputTuple, OutputValue>, bool>> as) {
			for (auto a : as) {
				actions.push_back(a);
			}
		}	

		void addAction(Action<InputTuple, OutputValue> a, bool b) {
			std::tuple<Action<InputTuple, OutputValue>, bool> t(a, b);
			actions.push_back(t);
		}
		void addDependency(std::string action, std::string dep, bool adj) {
			std::tuple<std::string, bool> depended = {dep, adj};
			dependencies.insert({action, depended});
		}	
	
		//Applies the actionset to two tuples n1 to n2.	
		OutputValue apply(InputTuple n1, InputTuple n2) {
			OutputValue output = {}; //Acceptable if Measurable is defined
						//with convertability in mind
			std::vector<std::string> taken = {};
			//For each action, check whether it should run, then calculate
			//distance to cumulatively add to the output.
			for (std::tuple<Action<InputTuple, OutputValue>, bool> a 
					: actions) {
					if (checkAction(std::get<0>(a).getID(), 
								std::get<1>(a),
								taken)) {
						output = output + 
						   std::get<0>(a).distance(n1, n2);
						taken.push_back(
						   std::get<0>(a).getID());
					}	
			}
			return output;	
		}

		std::vector<std::tuple<Action<InputTuple, OutputValue>, bool>>
			getActions() {
				return actions;
		}
		std::multimap<std::string, std::tuple<std::string, bool>> getDependencies() 			{
			return dependencies;
		}
};
