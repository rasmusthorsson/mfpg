#include "LayerList.h"
#include "HandPosition.h"

template <class InputTuple, class Output> class GraphSolver {
	protected:
		std::vector<std::tuple<HandPosition<InputTuple>, Output>> solution;
	public:
		virtual void solve(LayerList<InputTuple, Output>) = 0;
		virtual std::vector<std::tuple<HandPosition<InputTuple>, Output>>
			getSolution() = 0;
		GraphSolver() {};
};
