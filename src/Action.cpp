#include "Action.h"

template<OutputViable OutputValue>
Action<OutputValue>::Action(std::string s) : ID(s) {}

template<OutputViable OutputValue>
Action<OutputValue>::Action(condfun cond, distfun dist, std::string name) : ID(name) {
	std::function<distfun> wrapped_dist = dist;
	std::function<condfun> wrapped_cond = cond;
	distance_funs = std::vector<std::function<distfun>>{wrapped_dist};
	condition_funs = std::vector<std::function<condfun>>{wrapped_cond};
}

template<OutputViable OutputValue>
Action<OutputValue>::Action(std::function<condfun> cond, std::function<distfun> dist, std::string name) : ID(name) {
	distance_funs = std::vector<std::function<distfun>>{dist};
	condition_funs = std::vector<std::function<condfun>>{cond};
}

template<OutputViable OutputValue>
Action<OutputValue>::~Action() {}

template<OutputViable OutputValue>
void Action<OutputValue>::addCondFun(condfun c) {
	std::function<condfun> wrapped_cond = c;
	condition_funs.push_back(c);
}

template<OutputViable OutputValue>
void Action<OutputValue>::addCondFun(std::function<condfun> c) {
	condition_funs.push_back(c);
}

template<OutputViable OutputValue>
void Action<OutputValue>::addDistFun(distfun d) {
	std::function<distfun> wrapped_dist = d;
	distance_funs.push_back(d);
}

template<OutputViable OutputValue>
void Action<OutputValue>::addDistFun(std::function<distfun> d) {
	distance_funs.push_back(d);
}

template<OutputViable OutputValue>
OutputValue Action<OutputValue>::distance(const PhysAttrMap& s1, const PhysAttrMap& s2) const {
	OutputValue acc = {};
	for (auto fun : distance_funs) {
		acc += fun(s1, s2);
	}
	return acc;
}

template<OutputViable OutputValue>
bool Action<OutputValue>::condition(const PhysAttrMap& s1, const PhysAttrMap& s2) const {
	bool acc = true;
	for (auto fun : condition_funs) {
		acc &= fun(s1, s2);
	}
	return acc;
}

template<OutputViable OutputValue>
std::string Action<OutputValue>::getID() const {
	return ID;
}

template<OutputViable OutputValue>
bool Action<OutputValue>::operator ==(const Action<OutputValue>& rhs) const {
	return (ID == rhs.ID);
}
