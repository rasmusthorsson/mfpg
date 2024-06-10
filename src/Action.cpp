#include "Action.h"

template<OutputViable OutputValue>
Action<OutputValue>::Action() {}

template<OutputViable OutputValue>
Action<OutputValue>::Action(std::string s) : ID(s) {}

template<OutputViable OutputValue>
Action<OutputValue>::Action(condfun cond, ACCUMULATOR c_a, distfun dist, ACCUMULATOR d_a, std::string name) : ID(name) {
	std::function<distfun> wrapped_dist = dist;
	std::function<condfun> wrapped_cond = cond;
	distance_funs = std::vector<std::pair<std::function<distfun>, ACCUMULATOR>>{std::make_pair(wrapped_dist, d_a)};
	condition_funs = std::vector<std::pair<std::function<condfun>, ACCUMULATOR>>{std::make_pair(wrapped_cond, c_a)};
}

template<OutputViable OutputValue>
Action<OutputValue>::Action(condfun cond, distfun dist, std::string name) : ID(name) {
	std::function<distfun> wrapped_dist = dist;
	std::function<condfun> wrapped_cond = cond;
	distance_funs = std::vector<std::pair<std::function<distfun>, ACCUMULATOR>>{std::make_pair(wrapped_dist, ACCUMULATOR::PLUS)};
	condition_funs = std::vector<std::pair<std::function<condfun>, ACCUMULATOR>>{std::make_pair(wrapped_cond, ACCUMULATOR::OR)};
}

template<OutputViable OutputValue>
Action<OutputValue>::Action(std::function<condfun> cond, ACCUMULATOR a_c, std::function<distfun> dist, ACCUMULATOR a_d, std::string name) : ID(name) {
	distance_funs = std::vector<std::pair<std::function<distfun>, ACCUMULATOR>>{std::make_pair(dist, a_c)};
	condition_funs = std::vector<std::pair<std::function<condfun>, ACCUMULATOR>>{std::make_pair(cond, a_d)};
}

template<OutputViable OutputValue>
Action<OutputValue>::~Action() {}

template<OutputViable OutputValue>
void Action<OutputValue>::addCondFun(condfun c, ACCUMULATOR a) {
	std::function<condfun> wrapped_cond = c;
	condition_funs.push_back(std::make_pair(wrapped_cond, a));
}

template<OutputViable OutputValue>
void Action<OutputValue>::addCondFun(std::function<condfun> c, ACCUMULATOR a) {
	condition_funs.push_back(std::make_pair(c, a));
}

template<OutputViable OutputValue>
void Action<OutputValue>::addDistFun(distfun d, ACCUMULATOR a) {
	std::function<distfun> wrapped_dist = d;
	distance_funs.push_back(std::make_pair(wrapped_dist, a));
}

template<OutputViable OutputValue>
void Action<OutputValue>::addDistFun(std::function<distfun> d, ACCUMULATOR a) {
	distance_funs.push_back(std::make_pair(d, a));
}

template<OutputViable OutputValue>
OutputValue Action<OutputValue>::distance(const NoteAttributes& s1, const NoteAttributes& s2) const {
	OutputValue acc = {};
	for (auto fun : distance_funs) {
		if (fun.second == ACCUMULATOR::PLUS) {
			acc += fun.first(s1, s2);
		} else if (fun.second == ACCUMULATOR::MINUS) {
			acc -= fun.first(s1, s2);
		}
	}
	return acc;
}

template<OutputViable OutputValue>
bool Action<OutputValue>::condition(const NoteAttributes& s1, const NoteAttributes& s2) const {
	bool acc = false;
	for (auto fun : condition_funs) {
		if (fun.second == ACCUMULATOR::AND) {
			acc &= fun.first(s1, s2);
		} else if (fun.second == ACCUMULATOR::OR) {
			acc |= fun.first(s1, s2);
		}
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
