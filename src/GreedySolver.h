#ifndef GREEDY_SOLVER_H_MFPG
#define GREEDY_SOLVER_H_MFPG

#include "GraphSolver.h"
#include "SolverException.h"
#include "LayerList.h"

//This does not find the shortest path of the graph, instead if finds a path through
//the graph that results in the shortest distance between each layer. Only to be
//used for testing purposes. Might get removed in future versions.
class GreedySolver : public virtual GraphSolver<std::tuple<int, int, int>, int> {
		using in_type = std::tuple<int, int, int>;
		using out_type = int;
	private:
		const std::tuple<int, int> findCheapest(LayerList<in_type, out_type>, 
								in_type) const;
	public:
		GreedySolver() {}
		void solve(LayerList<in_type, out_type>);
};
#endif
