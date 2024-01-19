#ifndef ACTION_H_MFPG
#define ACTION_H_MFPG

//Applying constraints on the output. 
//TODO Move somewhere else and make all outputs subject to these constraints. 
//TODO add another for inputs.
template<typename T>
concept OutputViable = requires(T a, T b) {
	a = {};
	a > b;
};

//Class for defining costs for actions, InputTuple defines tuple structure of input 
//(dictated by how note tuples are defined). OutputValue is for the output structure,
//generally int or float.
template <class InputTuple, OutputViable OutputValue> class Action {
	typedef OutputValue (*distfun)(InputTuple, InputTuple);
	private:
		std::string ID;
		distfun distFun;
	public:
		//Keep in header file for compilation reasons.
		Action(distfun fun, std::string name) : ID(name) {
			distFun = fun;
		} 
		OutputValue distance(InputTuple s1, InputTuple s2) const {
			return distFun(s1, s2);
		}
		std::string getID() {
			return ID;
		}
};
#endif
