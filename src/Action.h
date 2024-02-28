#ifndef ACTION_H_MFPG
#define ACTION_H_MFPG

#include "PhysAttrMap.h"

//Applying constraints on the output. 
template<typename T>
concept OutputViable = requires(T a, T b) {
	a = {};
	a > b;
};

//Class for defining costs for actions, PhysAttrMap defines tuple structure of input 
//(dictated by how note tuples are defined). OutputValue is for the output structure,
//generally int or float.
template <OutputViable OutputValue> class Action {
	typedef OutputValue (*distfun) (PhysAttrMap, PhysAttrMap);
	typedef bool (*condfun) (PhysAttrMap, PhysAttrMap);
	private:
		//Action name.
		std::string ID;

		//Function calculating the distance between two nodes.
		distfun distance_fun;

		//Function calculating whether the action was taken.
		condfun condition_fun;
	public:
		Action(condfun cond, distfun dist, std::string name) : ID(name) {
			distance_fun = dist;
			condition_fun = cond;
		} 
		~Action() {}

		//Apply the distance function to two tuples.
		OutputValue distance(const PhysAttrMap& s1, const PhysAttrMap& s2) const {
			return distance_fun(s1, s2);
		}

		//Apply the condition function to two tuples.
		bool condition(const PhysAttrMap& s1, const PhysAttrMap& s2) const {
			return condition_fun(s1, s2);
		}

		std::string getID() const {
			return ID;
		}

		friend bool operator ==(const Action<OutputValue>& lhs, 
					const Action<OutputValue>& rhs) {
			return (lhs.ID == rhs.ID);
		}
};
#endif
