#include "GreedySolver.h"

void GreedySolver::solve(LayerList<in_type, out_type>& ls) {
	in_type res_tuple;
	out_type new_output;
	out_type output;
	int edge_index;
	std::tuple<int, int> temp_tuple;
	bool first_layerlist = true;

	//Iterate through all layerlists.
	for (auto& layerlist : ls) {

		//First layer must check all nodes for the best starting point.
		if (first_layerlist) {
			first_layerlist = false;
			bool first_transition_tuple = true;

			//Iterate through all nodes and select best starting point.
			for (auto transition : layerlist.getTransitions()) {
				temp_tuple = findCheapest(layerlist, transition.first);
				new_output = std::get<0>(temp_tuple);

				//Set output on first tuple.
				if (first_transition_tuple) {
					first_transition_tuple = false;
					output = new_output;
					res_tuple = transition.first;
					edge_index = std::get<1>(temp_tuple);
				}
				if (new_output < output) {
					res_tuple = transition.first;
					output = new_output;
					edge_index = std::get<1>(temp_tuple);
				}
				//If no transition out and not last note, throw 
				//exception.
				if (layerlist.getNext() != NULL && edge_index < 0) {
					throw SolverException(std::string(
					  "Solver could not find a solution, no "
					  "transitions between two layers."
					  ));
				}
			}
		} else {
			res_tuple = layerlist.getElem()[edge_index];
			temp_tuple = findCheapest(layerlist, res_tuple);
			output = std::get<0>(temp_tuple);
			edge_index = std::get<1>(temp_tuple);
			
			if (layerlist.getNext() != NULL && edge_index < 0) {
				throw SolverException(std::string("Solver could not" 
				  "find a solution, no transitions between two layers."
				  ));
			}
		}
		const HandPosition<in_type, out_type> hp(res_tuple, 
					   layerlist.getElem().getNote(), 
					   layerlist);

		const std::tuple<HandPosition<in_type, out_type>, out_type> 
								t(hp, output);

		solution.push_back(t);
	}
}

const std::tuple<int, int> GreedySolver::findCheapest(
						LayerList<in_type, out_type>& ls, 
						const in_type& prev) const {
	const std::vector<int>& transitions = ls.getTransitions()[prev];
	int output = -1;
	int next = -1;
	for (int i = 0; i < transitions.size(); i++) {
		if (i == 0) {
			output = transitions[0];
			next = 0;
		} else if (transitions[i] < output) {
			output = transitions[i];
			next = i;
		}
	}
	return std::tuple<int, int>{output, next};
}
