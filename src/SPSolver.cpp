#include "SPSolver.h"
#include "SolverException.h"
#include "Log.h"

#include <limits.h>

template<typename Output>
SPSolver<Output>::SPSolver(int opt) : opt_level(opt) {}

template<typename Output>
SPSolver<Output>::SPSolver() : opt_level(0) {}

template<typename Output>
SPSolver<Output>::~SPSolver() {}

template<typename Output>
void SPSolver<Output>::removeNode(std::map<int, std::vector<int>>& unvisited, 
				 std::pair<int, int> current_node) {
	//Find specified node in unvisited, indexed by layer first.
	for (auto itr = unvisited[current_node.first].cbegin(); itr != unvisited[current_node.first].cend(); itr++) { 
		if (*itr == current_node.second) {
			//If node is last unvisited node in layer the entire layer is removed.
			if (unvisited[current_node.first].size() == 1) {
				if (!unvisited.erase(current_node.first)) {
					throw (SolverException(std::string("Failed to erase empty layer from unvisited."), current_node.first));
				}
				//If every node in layer has been visited, then all previous layers
				//can be safely invalidated. (opt_level 1).
				if (opt_level >= 1) {
					for (int i = 0; i < current_node.first; i++) {
						unvisited.erase(i);
					}
				}
			} else {
				unvisited[current_node.first].erase(itr);
			}
			return;
		}
	}	
	throw (SolverException(std::string("Could not remove node from layer in unvisited nodelist."), current_node.first));
}
			
template<typename Output> 
void SPSolver<Output>::calculateNB(LayerList<Output>& list, 
				  std::map<int, std::vector<int>>& unvisited,
				  std::pair<int, int> current_node, 
				  std::vector<std::vector<Output>>& dist, 
				  std::vector<std::vector<std::pair<int, int>>>& prev) {
	//Must check if all neighbours in next layer have been removed otherwise the map will 
	//construct an empty neighbour vector for the next layer.
	if (unvisited.count(current_node.first + 1) != 0) {
		for (auto itr = unvisited[current_node.first + 1].cbegin(); 
			  itr != unvisited[current_node.first + 1].cend(); itr++) {	   
			//Calculate new value of dist for neighbour to be dist of
			//current node + cost of transition to neighbour.
			Output alt = dist[current_node.first][current_node.second] + 
				     list.getList(current_node.first).		   
				     getTransitions()[current_node.second][*itr];
			if (alt < dist[current_node.first + 1][*itr]) { 
				  dist[current_node.first + 1][*itr] = alt; 
				  prev[current_node.first + 1][*itr] = current_node; 
			}
		}
	}
}

template<typename Output>
std::pair<int, int> SPSolver<Output>::findCheapest(std::map<int, std::vector<int>>& unvisited,
						   std::vector<std::vector<Output>>& dist) {
	std::pair<int, int> current_node({-1, -1});
	int cost = INT_MAX;
	//For all unvisited nodes, find one with lowest dist
	for (auto outer_itr = unvisited.crbegin(); outer_itr != unvisited.crend(); outer_itr++) {
		for (auto inner_itr = outer_itr->second.begin(); inner_itr != outer_itr->second.end(); inner_itr++) {
			if (dist[outer_itr->first][*inner_itr] < cost) {
				cost = dist[outer_itr->first][*inner_itr];
				current_node = std::make_pair(outer_itr->first, *inner_itr);
			}
		}
	}
	if (current_node.first == -1) {
		throw (SolverException(std::string("Could not find any unvisited nodes."), unvisited.size()));
	}
	return current_node;
}

template<typename Output>
void SPSolver<Output>::solve(LayerList<Output>& list) {		

	std::vector<std::vector<Output>> dist; //Keeps track of minimum distance to node [n][m]
	std::vector<std::vector<std::pair<int, int>>> prev; //Stores next node in minimum path to start from
							    //node [n][m]
	std::map<int, std::vector<int>> unvisited; //Stores unvisited nodes, starts filled with all nodes. 

	//Fill temporary graph structures with default values to shape them according to the graph in list.
	int layer_index = 0;
	for (auto& l : list) { 	
		std::vector<Output> current_dist;
		std::vector<std::pair<int, int>> current_prev;
		std::vector<int> current_unvisited;
		for (int i = 0; i < l.getElem().getSize(); i++) { 
			current_dist.push_back(INT_MAX);
			current_prev.push_back({-1, -1});
			current_unvisited.push_back(i);
		}
		unvisited.insert(make_pair(layer_index, current_unvisited));
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

		removeNode(unvisited, current_node);

		//If current node is in the last layer it is a target and has no neighbors.
		if (current_node.first < dist.size() - 1) { 
			calculateNB(list, unvisited, current_node, dist, prev);
		//Opt level less than 2 if all targets should be explored.
		} else if (opt_level >= 2) {
			//if we reach a target we have a solution.
			break;
		}
	}

	int d_size = dist.size();
	int ll_size = dist[d_size - 1].size();

	int best = INT_MAX;
	std::pair<int, int> best_pos({-1, -1});

	//Since we can have several targets (all nodes in the last layer) we look for the target with the 
	//lowest dist cost.
	for (int i = 0; i < ll_size; i++) { 
		if (dist[d_size - 1][i] < best) {
			best = dist[d_size - 1][i];
			best_pos = std::make_pair(d_size - 1, i);
		}	
	}
	if (best_pos.first == -1 || best == INT_MAX) {
		throw SolverException("Could not find a solved target after running algorithm.", dist.size() - 1);
	}
	
	std::pair<int, int> sol = best_pos; 	
	std::vector<std::pair<int, int>> path(prev.size(), std::make_pair(-1, -1));

	//Store best path
	for (int i = path.size() - 1; i >= 0; i--) {
		path[i] = sol;
		sol = prev[sol.first][sol.second];
	}
	mfpg_log::Log::verbose_out(std::cout,
			"Solution found in " + std::to_string(count) + " iterations.\n",
			mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL
			);

	//Traverse path and store nodes and transition costs in solution.
	for (int i = 0; i < path.size(); i++) { 
		PhysAttrMap m = list.getList(path[i].first).getElem()[path[i].second];
		const LayerList<Output>& l = list.getList(path[i].first);
		SimplifiedNote n = list.getList(path[i].first).getElem().getNote();

		HandPosition<Output> hp(m, n, l);

		//Final transition cost is -1.
		Output t_cost = -1;
		if (i != path.size() - 1) {
			t_cost = list.getList(i).getTransitions()[path[i].second][path[i+1].second];
		} 

		this->solution.push_back(std::tuple<HandPosition<Output>, Output>({hp, t_cost}));
	}
}
