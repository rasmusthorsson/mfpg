#ifndef ACTION_H_MFPG
#define ACTION_H_MFPG

//Applying constraints on the output. 
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
		OutputValue distance(const InputTuple& s1, const InputTuple& s2) const {
			return distance_fun(s1, s2);
		}
		bool condition(const InputTuple& s1, const InputTuple& s2) const {
			return condition_fun(s1, s2);
		}
		std::string getID() const {
			return ID;
		}
};
#endif
