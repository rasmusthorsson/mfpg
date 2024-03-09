#ifndef SP_SOLVER_MFPG_H
#define SP_SOLVER_MFPG_H

#include "GraphSolver.h"

template<class Output> class SPSolver : public virtual GraphSolver<Output> {
	private:
		//Level of optimization, incremental inclusion: 
		//0 = none 
		//1 = early invalidation of previous layers upon visitation of an entire layer
		int opt_level = 0;
		//Helper to remove a node from the visited list.
		void removeNode(std::vector<std::pair<int, int>>&, std::pair<int, int>, std::vector<int>&);
		//Helper to calculate new neighbour distances and previous paths.
		void calculateNB(LayerList<Output>&,
				std::vector<std::pair<int, int>>&,
				std::pair<int, int>,
				std::vector<std::vector<Output>>&, 
				std::vector<std::vector<std::pair<int, int>>>&);
		//Helper to find the node with the cheapest dist cost.
		std::pair<int, int> findCheapest(std::vector<std::pair<int, int>>&,
						 std::vector<std::vector<Output>>&);
	public:
		SPSolver(int); 
		SPSolver(); 
		~SPSolver();

		void solve(LayerList<Output>&) override;

};
#endif
