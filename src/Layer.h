#include "SimplifiedNote.h"
#include "NodeException.h"
#include <vector>
#include <cassert>
#include "NoteEnums.h"

//Class to represent a layer of nodes, each layer corresponds to a note in the music piece,
//a node is generally a user-defined tuple, (simple example is a 3-tuple of ints representing
//String, Hand Position, and Finger Position).
template<class NodeTuple> class Layer {
	private:
		const SimplifiedNote note;
		std::vector<NodeTuple> nodes;
	public:
		//Defined here due to wildcard compilation issues, according to isocpp.org.
		Layer(SimplifiedNote n) : note(n), nodes() {}
		Layer(SimplifiedNote n, NoteMapper<NodeTuple>* mapper) 
			: note(n) 
		{
			auto range = mapper->getRange(n.getNote());
			for (auto i = range.first; i != range.second; ++i) {
				addNode(i->second);
			}
		}
		//Attempts to add a node to a layer, if node is already present does nothing and 
		//returns -1.
		int addNode(NodeTuple n) {
        		int old_size = nodes.size();
        		for (auto i = nodes.begin(); i != nodes.end(); i++) {
				if (n == *i) {
					return -1;
				}
			}
			nodes.push_back(n);
        		if (!(nodes.size() == old_size + 1)) {
        			return -1;
			}
			return 1;
		}
		
		//Attempts to remove a node from a layer, throws exception if node is no present.
		int removeNode(NodeTuple n) {
			if (nodes.size() < 1) {
				return -1;
			}
			for (auto i = nodes.begin(); i != nodes.end(); i++) {
				if (n == *i) {
					nodes.erase(i);
					return 1;
				}
			}
			return -1;
		}

		std::vector<NodeTuple> getNodes() {
			return nodes;
		}

		int getSize() {
			return nodes.size();
		}

		void clear() {
			nodes.clear();
		}
		SimplifiedNote getNote() {
			return note;
		}
};
