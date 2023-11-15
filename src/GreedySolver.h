#include "GraphSolver.h"

//Temporary version for a greedy solver.
class GreedySolver : public virtual GraphSolver<std::tuple<int, int, int>, int> {
	public:
		GreedySolver() {}
		void solve(LayerList<std::tuple<int, int, int>, int> ls) {
			std::tuple<int, int, int> current_tuple;
			bool first = true;
			int old_count = 0;
			int count = 0;
			int current_cost = 10000000;
			for (auto layerlist : ls) {
				if (first) {
					first = false;
					for (auto transitionTuple : 
						layerlist.getTransitions()) {
						count = 0;
						for (int output : 
							transitionTuple.second) {
							if (current_cost > output) {
								current_cost = 
								 output;
								current_tuple = 
								 transitionTuple.first;
								old_count = count;
							}
						count++;
						}
					}
				} else if (layerlist.getNext() == NULL) {
					current_tuple = layerlist
							.getElem()
							.getNodes()
							[old_count];
				} else {
					count = 0;
					current_cost = 10000000;
					auto elem_nodes = layerlist.getElem()
									.getNodes();
					auto next_tuple = layerlist
								.getTransitions()
								.find(elem_nodes
								[old_count]);
					for (auto output : next_tuple->second) { 
						if (current_cost > output) {
							current_cost = output;
							current_tuple = layerlist
									.getElem()
									.getNodes()
									[old_count];
							old_count = count;
						}
					count++;
					}
					count--;
				}
				HandPosition<std::tuple<int, int, int>> 
								hp(current_tuple);
				std::tuple<HandPosition
					<std::tuple<int, int, int>>, int> tuple(
					hp, current_cost);
				solution.push_back(tuple);
			}
		}
		std::vector<std::tuple<HandPosition<std::tuple<int, int, int>>, int>>
			getSolution() {
				return solution;
			}
};
