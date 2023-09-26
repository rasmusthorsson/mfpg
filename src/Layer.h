#include "SimplifiedNote.h"
#include "NodeException.h"
#include <vector>
#include <cassert>

//Class to represent a layer of nodes, each layer corresponds to a note in the music piece,
//a node is generally a user-defined tuple, (simple example is a 3-tuple of ints representing
//String, Hand Position, and Finger Position).
template<class T> class Layer {
	private:
		const simplifiednote::SimplifiedNote note;
		std::vector<T> nodes;
	public:
		//Defined here due to wildcard compilation issues, according to isocpp.org.
		Layer(simplifiednote::SimplifiedNote n) : note(n), nodes() {}
		//Attempts to add a node to a layer.
		void addNode(T n) {
        		int old_size = nodes.size();
        		for (auto i = nodes.begin(); i != nodes.end(); i++) {
				if (n == *i) {
					throw NodeException<T>("Node already exists within layer."
							, n, note);
				}
			}
			nodes.push_back(n);
        		if (!(nodes.size() == old_size + 1)) {
                		throw NodeException<T>("Could not add node to note layer.", n, note);
        		}
		}
		
		//Attempts to remove a node from a layer, throws exception if node is no present.
		void removeNode(T n) {
			if (nodes.size() < 1) {
				throw NodeException(
					"Can not remove node from note layer, note layer is empty."
						, n, note);
			}
			for (auto i = nodes.begin(); i != nodes.end(); i++) {
				if (n == *i) {
					nodes.erase(i);
					return;
				}
			}
			throw NodeException("Could not locate node in note layer.", n, note);
		}

		std::vector<T> getNodes() {
			return nodes;
		}

		int getSize() {
			return nodes.size();
		}

		void clear() {
			nodes.clear();
		}
};
