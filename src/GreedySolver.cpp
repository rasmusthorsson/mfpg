#include "GreedySolver.h"

void GreedySolver::solve(LayerList<out_type>& ls) {

	PhysAttrMap res_node;
	out_type new_output;
	out_type output;
	int edge_index;
	std::tuple<int, int> next_tuple;
	bool first_layerlist = true;

	int count = 0;
	//Iterate through all layerlists.
	for (auto& layerlist : ls) {
		count++;
		//First layer must check all nodes for the best starting point.
		if (first_layerlist) {
			first_layerlist = false;
			bool first_transition_tuple = true;

			//Iterate through all nodes and select best starting point.
			for (int i = 0; i < layerlist.getTransitions().size(); i++) {
				next_tuple = findCheapest(layerlist, i);
				new_output = std::get<0>(next_tuple);

				//Set output on first tuple.
				if (first_transition_tuple) {
					first_transition_tuple = false;
					output = new_output;
					res_node = layerlist.getElem()[i];
					edge_index = std::get<1>(next_tuple);
				}
				if (new_output < output) {
					res_node = layerlist.getElem()[i];
					output = new_output;
					edge_index = std::get<1>(next_tuple);
				}
		
				if (layerlist.getNext() != NULL && edge_index < 0) {
					throw SolverException(std::string("Solver could not find a "
					  "solution, no transitions between two layers."), count); 
				}
			}
		} else {
			res_node = layerlist.getElem()[edge_index];
			next_tuple = findCheapest(layerlist, edge_index);
			output = std::get<0>(next_tuple);
			edge_index = std::get<1>(next_tuple);
			
			if (layerlist.getNext() != NULL && edge_index < 0) {
				throw SolverException(std::string("Solver could not " 
				  "find a solution, no transitions between two layers."), count);
			}
		}

		const HandPosition<out_type> hp(res_node, layerlist.getElem().getNote(), layerlist);
		const std::tuple<HandPosition<out_type>, out_type> t(hp, output);

		solution.push_back(t);
	}
}

const std::tuple<int, int> GreedySolver::findCheapest(LayerList<out_type>& ls, int prev) const {
	int transition_cost = -1;
	int next_index = -1;
	if (ls.getTransitions().size() == 0) { //Should only happen on last note.
		return std::tuple<int, int>{transition_cost, next_index};
	}
	const std::vector<int>& transitions = ls.getTransitions()[prev];
	for (int i = 0; i < transitions.size(); i++) {
		if (i == 0) {
			transition_cost = transitions[0];
			next_index = 0;
		} else if (transitions[i] < transition_cost) {
			transition_cost = transitions[i];
			next_index = i;
		}
	}
	return std::tuple<int, int>{transition_cost, next_index};
}
