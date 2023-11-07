#include "Action.h"
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <map>

//Probably move this to Action.h?
template<typename T>
concept Measurable = requires(T a, T b) {
	a + b; //Placeholder
	//TODO define concept for measurablility for output
};

template <class InputTuple, class OutputValue> 
class ActionSet {
	private:
		std::vector<std::tuple<Action<InputTuple, OutputValue>, bool>> actions;
		std::multimap<std::string, std::tuple<std::string, bool>> eventmap;

		//if default = true check with ||, if default = false check with &&

		

		bool checkAction(std::string actionName, bool _default, 
				std::vector<std::string> previousEvents) {
			std::vector<bool> bools;
			for (std::tuple<std::string, bool> event 
					: eventmap.find(actionName)) {
				if (std::find(previousEvents.begin(),
					      previousEvents.end(),
					      std::get<0>(event)) !=
					      previousEvents.end()) {
					bools.push_back(std::get<1>(event));
				}
			}
			bool ret = _default;
			for (bool b : bools) {
				if (_default) {
					ret = ret || b;
				} else {
					ret = ret && b;
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
		
		OutputValue apply(InputTuple n1, InputTuple n2) {
			OutputValue output = 0; //Acceptable if Measurable is defined
						//with convertability in mind
			std::vector<std::string> taken = {};
			for (std::tuple<Action<InputTuple, OutputValue>, bool> a 
					: actions) {
					output = output + std::get<0>(a).distance(n1, n2);
			}
			return output;	
		}

		std::vector<std::tuple<Action<InputTuple, OutputValue>, bool>>
			getActions() {
				return actions;
		}
		std::multimap<std::string, std::tuple<std::string, bool>> getEventMap() {
			return eventmap;
		}
};
