#ifndef ACTION_H_MFPG
#define ACTION_H_MFPG

#include "PhysAttrMap.h"
#include <vector>
#include <functional>

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
	typedef OutputValue (distfun) (PhysAttrMap, PhysAttrMap);
	typedef bool (condfun) (PhysAttrMap, PhysAttrMap);
	private:
		//Action name.
		std::string ID;
		//Function calculating the distance between two nodes.
		std::vector<std::function<distfun>> distance_funs;
		//Function calculating whether the action was taken.
		std::vector<std::function<condfun>> condition_funs;
	public:
		Action(std::string);
		Action(condfun, distfun, std::string);
		Action(std::function<condfun>, std::function<distfun>, std::string);
		Action();
		~Action();

		void addCondFun(condfun c);
		void addDistFun(distfun d);

		void addCondFun(std::function<condfun> c);
		void addDistFun(std::function<distfun> d);

		//Apply the distance function to two tuples.
		OutputValue distance(const PhysAttrMap&, const PhysAttrMap&) const;
		//Apply the condition function to two tuples.
		bool condition(const PhysAttrMap&, const PhysAttrMap&) const;

		std::string getID() const;
		bool operator ==(const Action<OutputValue>&) const;
};
#endif
