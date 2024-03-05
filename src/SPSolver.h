#include "GraphSolver.h"

template<class Output> class SPSolver : public virtual GraphSolver<Output> {
	public:
		SPSolver(); 
		~SPSolver();

		void solve(LayerList<Output>&) override;

};
