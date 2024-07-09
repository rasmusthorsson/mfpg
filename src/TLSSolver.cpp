#include "TLSSolver.h"
#include "PhysAttrMap.h"

template<class Output>
TLSSolver<Output>::TLSSolver() {};

template<class Output>
void TLSSolver<Output>::solve(LayerList<Output>& list) {
	std::vector<std::tuple<LayerList<Output>&, int>> sorted_nodes;
	std::vector<int> shortest_dist;
	std::vector<int> predecessors;
	bool f = true;
	for (auto &l : list) {
		for (int i = 0; i < l.getElem().getSize(); i++) {
			sorted_nodes.push_back({l, i});
			if (f) {
				shortest_dist.push_back(0);
			} else {
				shortest_dist.push_back(100000);
			}
			predecessors.push_back(-1);
		}
		f = false;
	}
	int prev_size = std::get<0>(sorted_nodes[0]).getElem().getSize();

	//Iterate through all nodes except for the starting nodes (as they do not have edges going to them).
	for (int node = std::get<0>(sorted_nodes[0]).getElem().getSize(); node < 
			sorted_nodes.size(); node++) {


		for (int prev_node = node - std::get<1>(sorted_nodes[node]) - prev_size;
				prev_node < node - std::get<1>(sorted_nodes[node]); prev_node++) {

			if (shortest_dist[node] > shortest_dist[prev_node] + 
				std::get<0>(sorted_nodes[prev_node]).getTransitions()[
				std::get<1>(sorted_nodes[prev_node])][
				std::get<1>(sorted_nodes[node])]) {
				
				shortest_dist[node] = shortest_dist[prev_node] + 
					std::get<0>(sorted_nodes[prev_node]).getTransitions()[
					std::get<1>(sorted_nodes[prev_node])][
					std::get<1>(sorted_nodes[node])];
				
				predecessors[node] = prev_node;
			}
		} 
		if (std::get<1>(sorted_nodes[node]) + 1 >= std::get<0>(sorted_nodes[node]).getElem()
				.getSize()) {
			prev_size = std::get<0>(sorted_nodes[node]).getElem().getSize();
		}
	}
	std::vector<int> sol;
	int lowest = 10000;
	int index = 0;
	for (int i = shortest_dist.size() - get<0>(sorted_nodes[sorted_nodes.size() - 1])
			.getElem().getSize(); i < shortest_dist.size(); i++) {
		if (shortest_dist[i] < lowest) {
			lowest = shortest_dist[i];
			index = i;
		}
	}
	while (index > -1) {
		sol.push_back(std::get<1>(sorted_nodes[index]));
		std::cout << "Cost: " << shortest_dist[index] << "\n";
		index = predecessors[index];
	}
	std::vector<int> rev_sol;
	for (int i = sol.size() - 1; i >= 0; i--) {
		rev_sol.push_back(sol[i]);
	}
	for (int i = 0; i < rev_sol.size(); i++) {
		HandPosition<Output> hp(list.getList(i).getElem().getNodes()[rev_sol[i]], 
			list.getList(i).getElem().getNote(), list.getList(i));
		if (i < rev_sol.size() - 1) {
			this->solution.push_back({hp, list.getList(i).getTransitions()[rev_sol[i]][rev_sol[i+1]]});
		} else {
			this->solution.push_back({hp, -1});
		}
	}
}
