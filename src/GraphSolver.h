#ifndef GRAPH_SOLVER_H_MFPG
#define GRAPH_SOLVER_H_MFPG

#include "LayerList.h"
#include "HandPosition.h"

//Abstract class for a solver to the graph created representing the transitions 
//between notes. A shortest path graph algorithm is the intended algorithm to be
//implemented.
template <class InputTuple, class Output> class GraphSolver {
	protected:
		//solution vector represents the transitions for the solution and the
		//costs of each transition.
		std::vector<std::tuple<HandPosition<InputTuple, Output>, 
								Output>> solution;
	public:
		virtual void solve(LayerList<InputTuple, Output>) = 0;
		std::vector<std::tuple<HandPosition<InputTuple, Output>, 
						Output>> getSolution() const {
			return solution;
		};
		GraphSolver() {};
		virtual ~GraphSolver() {};
};
#endif
