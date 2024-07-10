#include "TLSSolver.h"
#include "PhysAttrMap.h"

#include <limits>

template<class Output>
TLSSolver<Output>::TLSSolver() {};

template<class Output>
void TLSSolver<Output>::solve(LayerList<Output>& list) {

	std::vector<std::tuple<LayerList<Output>&, int>> sorted_nodes;
	std::vector<int> shortest_dist;
	std::vector<int> predecessors;

	//Init vectors
	for (bool first = true; auto &l : list) {
		for (int i = 0; i < l.getElem().getSize(); i++) {
			//Sorted nodes contains a reference to the layerlist link, and the index of the
			//node in this link.
			sorted_nodes.push_back({l, i});
			if (first) {
				shortest_dist.push_back(0);
			} else {
				shortest_dist.push_back(INT_MAX);
			}
			predecessors.push_back(-1);
		}
		first = false;
	}

	//Previous size starts at the starting link, which can always be found from the first node.
	int prev_size = std::get<0>(sorted_nodes[0]).getElem().getSize();

	//Iterate through all nodes except for the starting nodes (as they do not have edges going to them).
	for (int node = std::get<0>(sorted_nodes[0]).getElem().getSize(); node < sorted_nodes.size(); 
			node++) {

		//For each node, iterate through all previous nodes which have edges going to that node. 
		//These are limited to nodes in the previous layer.
		for (int prev_node = node - std::get<1>(sorted_nodes[node]) - prev_size;
			prev_node < node - std::get<1>(sorted_nodes[node]); prev_node++) {

			if (shortest_dist[node] > shortest_dist[prev_node] + 
				std::get<0>(sorted_nodes[prev_node]).getTransitions()
				[std::get<1>(sorted_nodes[prev_node])]
				[std::get<1>(sorted_nodes[node])]) {
				
				shortest_dist[node] = shortest_dist[prev_node] + 
					std::get<0>(sorted_nodes[prev_node]).getTransitions()
					[std::get<1>(sorted_nodes[prev_node])]
					[std::get<1>(sorted_nodes[node])];
				
				predecessors[node] = prev_node;
			}
		} 
	
		//If the next node is part of a new layer, set prev size to this layer.
		if (std::get<1>(sorted_nodes[node]) + 1 >= std::get<0>(sorted_nodes[node]).getElem()
				.getSize()) {
			prev_size = std::get<0>(sorted_nodes[node]).getElem().getSize();
		}
	}

	std::vector<int> sol;

	int lowest = INT_MAX;
	int index = 0;

	//For all end nodes (nodes in the final layer), find the one with the lowest distance amd set the
	//index to it.
	for (int end_node = shortest_dist.size() - get<0>(sorted_nodes[sorted_nodes.size() - 1]).getElem()
			.getSize(); end_node < shortest_dist.size(); end_node++) {
		if (shortest_dist[end_node] < lowest) {
			lowest = shortest_dist[end_node];
			index = end_node;
		}
	}

	//All nodes will have predecessor indices except for the starting nodes, so we iterate through the
	//predecessors of our selected end-node and store the layer-relative index in the solution vector
	//and stop when the index is -1.
	while (index > -1) {
		sol.push_back(std::get<1>(sorted_nodes[index]));
		index = predecessors[index];
	}

	//Reverse the solution.
	std::vector<int> rev_sol;
	for (int i = sol.size() - 1; i >= 0; i--) {
		rev_sol.push_back(sol[i]);
	}

	//Iterate through the reversed solution and convert the indices to hand positions and costs.
	for (int i = 0; i < rev_sol.size(); i++) {
		HandPosition<Output> hp(list.getList(i).getElem().getNodes()[rev_sol[i]], 
			list.getList(i).getElem().getNote(), list.getList(i));
		if (i < rev_sol.size() - 1) {
			this->solution.push_back({hp, list.getList(i).getTransitions()[rev_sol[i]]
					[rev_sol[i+1]]});
		} else {
			//Final layer has no outgoing cost.
			this->solution.push_back({hp, -1});
		}
	}
}
