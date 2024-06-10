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
void ActionSet<OutputValue>::addAction(Action<OutputValue> a, bool b) {
	actions.push_back(std::tuple<Action<OutputValue>, bool>({a, b}));
}

template<OutputViable OutputValue>
int ActionSet<OutputValue>::makeAction(condfun cf, distfun df, std::string name, bool _default) {
	const Action<OutputValue> a(cf, ACCUMULATOR::OR, df, ACCUMULATOR::PLUS, name);
	if (checkUnique(a)) {
		actions.push_back(std::tuple<Action<OutputValue>, bool> {a, _default});
		return 1;
	}
	return -1;
}

template<OutputViable OutputValue>
int ActionSet<OutputValue>::makeAction(condfun cf, ACCUMULATOR ac, distfun df, ACCUMULATOR ad, std::string name, bool _default) {
	const Action<OutputValue> a(cf, ac, df, ad, name);
	if (checkUnique(a)) {
		actions.push_back(std::tuple<Action<OutputValue>, bool> {a, _default});
		return 1;
	}
	return -1;
}

template<OutputViable OutputValue>
void ActionSet<OutputValue>::addCondToAction(condfun cf, ACCUMULATOR ac, std::string s) {
	for (auto a : actions) {
		if (std::get<0>(a).getID() == s) {
			std::get<0>(a).addCondFun(cf, ac);	
		}
	}
}

template<OutputViable OutputValue>
void ActionSet<OutputValue>::addDistToAction(distfun df, ACCUMULATOR ad, std::string s) {
	for (auto a : actions) {
		if (std::get<0>(a).getID() == s) {
			std::get<0>(a).addDistFun(df, ad);
		}
	}
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
OutputValue ActionSet<OutputValue>::apply(const NoteAttributes& n1, const NoteAttributes& n2) const {
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
