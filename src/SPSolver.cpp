#include "SPSolver.h"
#include <memory>

template<typename Output>
SPSolver<Output>::SPSolver() {}

template<typename Output>
SPSolver<Output>::~SPSolver() {}

template<typename Output>
void SPSolver<Output>::solve(LayerList<Output>& list) {		
	std::vector<std::vector<Output>> dist;
	std::vector<std::vector<std::pair<int, int>>> prev;
	std::vector<std::pair<int, int>> nodes; 

	for (auto& l : list) { 	//Fill dist and prev with nothing values.
		Output o = 10000;	
		std::vector<Output> current_dist;
		std::vector<std::pair<int, int>> current_prev;
		for (int i = 0; i < l.getElem().getSize(); i++) { 
			current_dist.push_back(o);
			current_prev.push_back({-1, -1});
		}
		dist.push_back(current_dist);
		prev.push_back(current_prev);
	}
	int count = 0;
	for (auto& l : list) { //Fill nodes 
		for (int i = 0; i < l.getElem().getSize(); i++) { 
			nodes.push_back(std::make_pair(count, i));
		}
		count++;
	}
	for (int i = 0; i < dist[0].size(); i++) { //Set starting values for first layer to be 0
		dist[0][i] = 0;
	}
	int timeout = 0;
	while (nodes.size() > 0) { //Iterate through all nodes in nodes
		std::pair<int, int> next;
		int cost = 100000;
		for (int i = 0; i < dist.size(); i++) { //For all nodes, find one with lowest dist
			for (int j = 0; j < dist[i].size(); j++) { 
				if (dist[i][j] < cost) {
					for (auto itr = nodes.begin(); itr != nodes.end(); itr++) { 
						if (itr->first == i && itr->second == j) { //if unvisited
							cost = dist[i][j];
							next = std::make_pair(i, j);
							break;
						}
					}
				}
			}
		}
		for (auto itr = nodes.begin(); itr != nodes.end(); itr++) { //Remove from unvisited
			if (itr->first == next.first && itr->second == next.second) {
				nodes.erase(itr);
				break;
			}
		}
		if (next.first < dist.size() - 1) { //Last values wont have any neighbours to caluclate to
			for (int i = 0; i < list.getList(next.first+1).getElem().getSize(); i++) { //For all
				for (auto itr = nodes.begin(); itr != nodes.end(); itr++) {	   //neigh-
					if (itr->first == next.first + 1 && itr->second == i) {	   //bors
						Output alt = dist[next.first][next.second] + 	   //in un-
							list.getList(next.first).		   //visited
							getTransitions()[next.second][i];
						if (alt < dist[next.first + 1][i]) { //if new cost is lower
							dist[next.first + 1][i] = alt; //set new cost
							prev[next.first + 1][i] = next; //store node path
						}
					}
				}
			}
		}
	}
	int d_size = dist.size();
	int ll_size = dist[d_size - 1].size();
	int best = 10000;
	std::pair<int, int> best_pos({-1, -1});
	for (int i = 0; i < ll_size; i++) { //find node in last layer with lowest cost
		if (dist[d_size - 1][i] < best) {
			best = dist[d_size - 1][i];
			best_pos = std::make_pair(d_size - 1, i);
		}	
	}
	
	std::vector<std::pair<int, int>> path_rev;
	path_rev.push_back(best_pos);
	std::pair<int, int> sol = prev[best_pos.first][best_pos.second]; 

	while(sol.first != 0) { //Locate the reversed path
		path_rev.push_back(sol);
		sol = prev[sol.first][sol.second];
	}
	path_rev.push_back(sol);

	std::vector<std::pair<int, int>> path;
	for (int i = path_rev.size() - 1; i > -1; i--) { //Reverse the path
		path.push_back(path_rev[i]);
	}

	for (int i = 0; i < path.size(); i++) { //Wander path and store nodes and cost in solution

		PhysAttrMap m = list.getList(path[i].first).getElem()[path[i].second];
		const LayerList<Output>& l = list.getList(path[i].first);
		SimplifiedNote n = list.getList(path[i].first).getElem().getNote();

		HandPosition<Output> hp(m, n, l);

		Output final_cost = -1;
		if (i != path.size() - 1) {
			final_cost = list.getList(i)
						.getTransitions()[path[i].second][path[i+1].second];
		} 

		this->solution.push_back(std::tuple<HandPosition<Output>, Output>({hp, final_cost}));
	}
}
