#include "Action.h"

template<OutputViable OutputValue>
Action<OutputValue>::Action(condfun cond, distfun dist, std::string name) : ID(name) {
	distance_fun = dist;
	condition_fun = cond;
} 

template<OutputViable OutputValue>
Action<OutputValue>::~Action() {}

template<OutputViable OutputValue>
OutputValue Action<OutputValue>::distance(const PhysAttrMap& s1, const PhysAttrMap& s2) const {
	return distance_fun(s1, s2);
}

template<OutputViable OutputValue>
bool Action<OutputValue>::condition(const PhysAttrMap& s1, const PhysAttrMap& s2) const {
	return condition_fun(s1, s2);
}

template<OutputViable OutputValue>
std::string Action<OutputValue>::getID() const {
	return ID;
}

template<OutputViable OutputValue>
bool Action<OutputValue>::operator ==(const Action<OutputValue>& rhs) const {
	return (ID == rhs.ID);
}
