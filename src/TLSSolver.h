#ifndef TLS_SOLVER_H_MFPG
#define TLS_SOLVER_H_MFPG

#include "GraphSolver.h"
#include "LayerList.h"

//The LayerList is already topologically sorted as every node in Layer x < y is prior
//to Layer y for all layers.
template<class Output>
class TLSSolver : public virtual GraphSolver<Output> {
	private:
	public:
		TLSSolver();
		void solve(LayerList<Output>&);

};

#endif
