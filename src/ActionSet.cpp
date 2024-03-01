#include "ActionSet.h"

template<OutputViable OutputValue>
bool ActionSet<OutputValue>::checkAction(std::string action_name, bool _default, std::vector<std::string>& previous_actions) const {
	std::vector<bool> bools;
	for (auto [dep_itr, range_end] = dependencies.equal_range(action_name); 
	     dep_itr != range_end; 
	     dep_itr++) {

		if (find(previous_actions.begin(),
		    previous_actions.end(),
		    std::get<0>(dep_itr->second)) != previous_actions.end()) {
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

template<OutputViable OutputValue>
bool ActionSet<OutputValue>::checkUnique(const Action<OutputValue>& a) {
	for (const auto& as : actions) {
		if (std::get<0>(as) == a) {
			return false;
		}
	}
	return true;
}

template<OutputViable OutputValue>
ActionSet<OutputValue>::ActionSet() {};

template<OutputViable OutputValue>
ActionSet<OutputValue>::ActionSet(std::vector<std::tuple<Action<OutputValue>, bool>> as) {
	for (auto a : as) {
		if (checkUnique(std::get<0>(a))) {
			actions.push_back(a);
		}
	}
}

template<OutputViable OutputValue>
ActionSet<OutputValue>::ActionSet(Action<OutputValue> a, bool b) {
	actions.push_back({a, b});
}

template<OutputViable OutputValue>
ActionSet<OutputValue>::ActionSet(std::initializer_list<std::tuple<Action<OutputValue>, bool>> as) {
	for (auto& a : as) {
		if (checkUnique(std::get<0>(a))) {
			actions.push_back(a);
		}
	}
}	

template<OutputViable OutputValue>
ActionSet<OutputValue>::~ActionSet() {};

template<OutputViable OutputValue>
int ActionSet<OutputValue>::makeAction(condfun cf, distfun df, std::string name, bool _default) {
	const Action<OutputValue> a(cf, df, name);
	if (checkUnique(a)) {
		actions.push_back(std::tuple<Action<OutputValue>, bool> {a, _default});
		return 1;
	}
	return -1;
}

template<OutputViable OutputValue>
int ActionSet<OutputValue>::addDependency(std::string dependent, std::string dependency, bool adjustment) {
	std::tuple<std::string, bool> dep = {dependency, adjustment};
	if (dependencies.insert({dependent, dep}) != dependencies.end()) {
		return 1;
	} else {
		return -1;
	}
}	

template<OutputViable OutputValue>
OutputValue ActionSet<OutputValue>::apply(const PhysAttrMap& n1, const PhysAttrMap& n2) const {
	OutputValue output = {}; //output must be zero-initializable
	std::vector<std::string> taken = {};

	for (const std::tuple<Action<OutputValue>, bool>& a : actions) 
	{
		if (checkAction(std::get<0>(a).getID(), std::get<1>(a), taken) 
				&& std::get<0>(a).condition(n1, n2))
		{
			output = output + std::get<0>(a).distance(n1, n2);
			taken.push_back(std::get<0>(a).getID());
		}	
	}
	return output;	
}
