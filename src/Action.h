//Class for defining costs for actions, T defines tuple structure of input (dictated by how note
//tuples are defined). D is for the output structure, generally int or float.

template <class InputTuple, class OutputValue> class Action {
	typedef OutputValue (*distfun)(InputTuple, InputTuple);
	private:
		std::string ID;
		distfun dist_fun;
	public:
		//Keep in header file for compilation reasons.
		Action(distfun fun, std::string name) : ID(name) {dist_fun = fun;}; 
		OutputValue distance(InputTuple s1, InputTuple s2) const {return dist_fun(s1, s2);};
};
