#include "SPSolver.h"
#include <limits.h>

template<typename Output>
SPSolver<Output>::SPSolver() {}

template<typename Output>
SPSolver<Output>::~SPSolver() {}

template<typename Output>
void SPSolver<Output>::solve(LayerList<Output>& list) {		

	std::vector<std::vector<Output>> dist; //Keeps track of minimum distance to node [n][m]
	std::vector<std::vector<std::pair<int, int>>> prev; //Stores next node in minimum path to start from
							    //node [n][m]
	std::vector<std::pair<int, int>> unvisited; //Stores unvisited nodes, starts filled with all nodes. 

	//Fill temp matrices with base values to shape them according to the graph in list.
	int layer_index = 0;
	for (auto& l : list) { 	
		std::vector<Output> current_dist;
		std::vector<std::pair<int, int>> current_prev;
		for (int i = 0; i < l.getElem().getSize(); i++) { 
			current_dist.push_back(INT_MAX);
			current_prev.push_back({-1, -1});
			unvisited.push_back(std::make_pair(layer_index, i));
		}
		layer_index++;
		dist.push_back(current_dist);
		prev.push_back(current_prev);
	}
	for (int i = 0; i < dist[0].size(); i++) { //Set starting values for first layer to be 0
		dist[0][i] = 0;
	}
	int count = 0;
	while (unvisited.size() > 0) { //As long as there is a node unvisited.
		count++;
		std::pair<int, int> current_node;
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

		//Remove current node from unvisited.
		for (auto itr = unvisited.begin(); itr != unvisited.end(); itr++) { 
			if (itr->first == current_node.first && itr->second == current_node.second) {
				unvisited.erase(itr);
				break;
			}
		}

		//If current node is in the last layer it is a target and has no neighbors.
		if (current_node.first < dist.size() - 1) { 
			//Calculate new distance for all neighbours of current node, which is equivalent
			//of finding all nodes in layer[next.first + 1].
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
	}

	int d_size = dist.size();
	int ll_size = dist[d_size - 1].size();

	int best = INT_MAX;
	std::pair<int, int> best_pos({-1, -1});

	//Since we have several targets (all of last layer) we find the target with the lower dist cost.
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
