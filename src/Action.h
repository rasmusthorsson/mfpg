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
	typedef OutputValue (*distfun) (InputTuple, InputTuple);
	typedef bool (*condfun) (InputTuple, InputTuple);
	private:
		std::string ID;
		distfun distance_fun;
		condfun condition_fun;
	public:
		//Keep in header file for compilation reasons.
		Action(condfun cond, distfun dist, std::string name) : 
			ID(name) {
			distance_fun = dist;
			condition_fun = cond;
		} 
		OutputValue distance(InputTuple s1, InputTuple s2) 
			const {
			return distance_fun(s1, s2);
		}
		bool condition(InputTuple s1, InputTuple s2) {
			return condition_fun(s1, s2);
		}
		std::string getID() {
			return ID;
		}
};
#endif
