template <class T, class D> class Action {
	typedef D (*distfun)(T, T);
	private:
		distfun dist_fun;
	public:
		//Keep in header file for compilation reasons.
		Action(distfun fun) {dist_fun = fun;}; 
		D distance(T s1, T s2) {return dist_fun(s1, s2);};
};
