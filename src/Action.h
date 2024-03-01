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
		Action(condfun cond, distfun, std::string);
		~Action();

		//Apply the distance function to two tuples.
		OutputValue distance(const PhysAttrMap&, const PhysAttrMap&) const;
		//Apply the condition function to two tuples.
		bool condition(const PhysAttrMap&, const PhysAttrMap&) const;

		std::string getID() const;
		bool operator ==(const Action<OutputValue>&) const;
};
#endif
