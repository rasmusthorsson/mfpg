//Class for defining costs for actions, InputTuple defines tuple structure of input (dictated by how note
//tuples are defined). OutputValue is for the output structure, generally int or float.

//Output must be zero-initializable. Currently not very useful due to constraint
//being checked in later stages anyway, but a place to add constraints later.
template<typename T>
concept OutputViable = requires(T a, T b) {
	a = {};
	a > b;
};

template <class InputTuple, OutputViable OutputValue> class Action {
	typedef OutputValue (*distfun)(InputTuple, InputTuple);
	private:
		std::string ID;
		distfun dist_fun;
	public:
		//Keep in header file for compilation reasons.
		Action(distfun fun, std::string name) : ID(name) {dist_fun = fun;}; 
		OutputValue distance(InputTuple s1, InputTuple s2) const {return dist_fun(s1, s2);};
		std::string getID() {
			return ID;
		};
};
