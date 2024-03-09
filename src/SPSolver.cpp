#include "SPSolver.h"
#include "SolverException.h"
#include <limits.h>

template<typename Output>
SPSolver<Output>::SPSolver(int opt) : opt_level(opt) {}

template<typename Output>
SPSolver<Output>::SPSolver() : opt_level(0) {}

template<typename Output>
SPSolver<Output>::~SPSolver() {}

template<typename Output>
void SPSolver<Output>::removeNode(std::vector<std::pair<int, int>>& unvisited, 
				 std::pair<int, int> current_node,
				 std::vector<int>& layer_sizes) {
	for (auto itr = unvisited.begin(); itr != unvisited.end(); itr++) { 
		if (itr->first == current_node.first && itr->second == current_node.second) {
			unvisited.erase(itr);
			layer_sizes[current_node.first] -= 1;
			//If every node in layer has been visited, then all previous layers
			//can be safely invalidated.

			if (opt_level >= 1 && layer_sizes[current_node.first] == 0) {
				for (auto er_itr = unvisited.begin(); er_itr != unvisited.end(); er_itr++) {
					if (er_itr->first < current_node.first) {
						unvisited.erase(er_itr);
					}
				}
			}
			return;
		}
	}	
	throw (SolverException(std::string("Could not remove node from unvisited nodelist."), current_node.first));
}
			
template<typename Output> 
void SPSolver<Output>::calculateNB(LayerList<Output>& list, 
				  std::vector<std::pair<int, int>>& unvisited,
				  std::pair<int, int> current_node, 
				  std::vector<std::vector<Output>>& dist, 
				  std::vector<std::vector<std::pair<int, int>>>& prev) {
	for (int i = 0; i < list.getList(current_node.first+1).getElem().getSize(); i++) { 
		//Only unvisited neighbours are relevant.
		for (auto itr = unvisited.begin(); itr != unvisited.end(); itr++) {	   
			if (itr->first == current_node.first + 1 && itr->second == i) {	   
				//Calculate new value of dist for neighbour to be dist of
				//current node + cost of transition to neighbour.
				Output alt = dist[current_node.first][current_node.second] + 
					     list.getList(current_node.first).		   
					     getTransitions()[current_node.second][i];
				//If new value is lower than current dist value of neighbour
				//then set it.
				if (alt < dist[current_node.first + 1][i]) { 
					  dist[current_node.first + 1][i] = alt; 
					  prev[current_node.first + 1][i] = current_node; 
				}
			}
		}
	}
}

template<typename Output>
std::pair<int, int> SPSolver<Output>::findCheapest(std::vector<std::pair<int, int>>& unvisited,
						   std::vector<std::vector<Output>>& dist) {
	std::pair<int, int> current_node({-1, -1});
	int cost = INT_MAX;
	//For all nodes, find one with lowest dist
	for (int i = 0; i < dist.size(); i++) { 			
		for (int j = 0; j < dist[i].size(); j++) {
			//If unvisited node has lower dist than currently 
			if (dist[i][j] < cost) {
				//Iterate through all unvisited nodes.	
				for (auto itr = unvisited.begin(); itr != unvisited.end(); itr++) { 
					//Check if node is in unvisited.
					if (itr->first == i && itr->second == j) { 
						cost = dist[i][j];
						current_node = std::make_pair(i, j);
						break;
					}
				}
			}
		}
	}
	if (current_node.first == -1) {
		throw (SolverException(std::string("Could not find any unvisited nodes."), dist.size()));
	}
	return current_node;
}

template<typename Output>
void SPSolver<Output>::solve(LayerList<Output>& list) {		

	std::vector<std::vector<Output>> dist; //Keeps track of minimum distance to node [n][m]
	std::vector<std::vector<std::pair<int, int>>> prev; //Stores next node in minimum path to start from
							    //node [n][m]
	std::vector<std::pair<int, int>> unvisited; //Stores unvisited nodes, starts filled with all nodes. 
	std::vector<int> layer_sizes;

	//Fill temp matrices with base values to shape them according to the graph in list.
	int layer_index = 0;
	for (auto& l : list) { 	
		std::vector<Output> current_dist;
		std::vector<std::pair<int, int>> current_prev;
		int layer_size = 0;
		for (int i = 0; i < l.getElem().getSize(); i++) { 
			layer_size++;
			current_dist.push_back(INT_MAX);
			current_prev.push_back({-1, -1});
			unvisited.push_back(std::make_pair(layer_index, i));
		}
		layer_sizes.push_back(layer_size);
		layer_index++;
		dist.push_back(current_dist);
		prev.push_back(current_prev);
	}
	for (int i = 0; i < dist[0].size(); i++) { //Set starting values for first layer to be 0
		dist[0][i] = 0;
	}
	//Calculate shortest path: First find node with lowest dist value, then remove that node from the
	//unvisited nodes (as it is now visited), and finally calculate the new dist values for the
	//neighbours of that node.
	int count = 0;
	while (unvisited.size() > 0) { 
		//Count is just used for logging purposes.
		count++;
		std::pair<int, int> current_node = findCheapest(unvisited, dist);

		removeNode(unvisited, current_node, layer_sizes);

		//If current node is in the last layer it is a target and has no neighbors.
		if (current_node.first < dist.size() - 1) { 
			calculateNB(list, unvisited, current_node, dist, prev);
		}
	}

	int d_size = dist.size();
	int ll_size = dist[d_size - 1].size();

	int best = INT_MAX;
	std::pair<int, int> best_pos({-1, -1});

	//Since we have several targets (all nodes in the last layer) we look for the target with the lowest 
	//dist cost.
	for (int i = 0; i < ll_size; i++) { 
		if (dist[d_size - 1][i] < best) {
			best = dist[d_size - 1][i];
			best_pos = std::make_pair(d_size - 1, i);
		}	
	}
	
	std::pair<int, int> sol = best_pos; 	
	std::vector<std::pair<int, int>> path(prev.size(), std::make_pair(-1, -1));

	//Store best path
	for (int i = path.size() - 1; i >= 0; i--) {
		path[i] = sol;
		sol = prev[sol.first][sol.second];
	}
	std::cout << "Solution found in " << count << " iterations.\n";

	//Traverse path and store nodes and transition costs in solution.
	for (int i = 0; i < path.size(); i++) { 
		PhysAttrMap m = list.getList(path[i].first).getElem()[path[i].second];
		const LayerList<Output>& l = list.getList(path[i].first);
		SimplifiedNote n = list.getList(path[i].first).getElem().getNote();

		HandPosition<Output> hp(m, n, l);

		//Final transition cost is -1.
		Output final_cost = -1;
		if (i != path.size() - 1) {
			final_cost = list.getList(i).getTransitions()[path[i].second][path[i+1].second];
		} 

		this->solution.push_back(std::tuple<HandPosition<Output>, Output>({hp, final_cost}));
	}
}
