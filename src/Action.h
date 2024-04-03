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

//Accumulator for binding functions in actions together, for example two functions "f1, OR" and "f2, AND"
//will combine to be: "f1 AND f2". The accumulator of the first function is never used.
enum ACCUMULATOR {
	MINUS,
	PLUS,
	OR,
	AND
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
		//Functions calculating the distance between two nodes.
		std::vector<std::pair<std::function<distfun>, ACCUMULATOR>> distance_funs;
		//Functions calculating whether the action was taken.
		std::vector<std::pair<std::function<condfun>, ACCUMULATOR>> condition_funs;
	public:
		Action();
		Action(std::string);
		Action(condfun, ACCUMULATOR, distfun, ACCUMULATOR, std::string);
		Action(condfun, distfun, std::string);
		Action(std::function<condfun>, ACCUMULATOR, std::function<distfun>, ACCUMULATOR, std::string);
		~Action();

		//Add lambda expression as function with accumulator.
		void addCondFun(condfun, ACCUMULATOR);
		void addDistFun(distfun, ACCUMULATOR);

		//Add lambda function as function with accumulator.
		void addCondFun(std::function<condfun>, ACCUMULATOR);
		void addDistFun(std::function<distfun>, ACCUMULATOR);

		//Apply the distance functions to two tuples, uses the accumulators to bind functions
		//together.
		OutputValue distance(const PhysAttrMap&, const PhysAttrMap&) const;
		//Apply the condition functions to two tuples, uses the accumulators to bind functions
		//together.
		bool condition(const PhysAttrMap&, const PhysAttrMap&) const;

		std::string getID() const;
		bool operator ==(const Action<OutputValue>&) const;
		
};
#endif
