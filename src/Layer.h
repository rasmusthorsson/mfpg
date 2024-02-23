#ifndef LAYER_H_MFPG
#define LAYER_H_MFPG

#include "SimplifiedNote.h"
#include "NodeException.h"
#include "NoteEnums.h"
#include "NoteMapper.h"

#include <memory>
#include <vector>

//Class to represent a layer of nodes, each layer corresponds to a note in the music 
//piece, a node is generally a user-defined tuple, (simple example is a 3-tuple of 
//ints representing String, Hand Position, and Finger Position).
template<class InputTuple> class Layer {
	private:
		const SimplifiedNote note;
		
		//All possible ways to play a the note (as represented by the tuple,
		//calculated by the notemapper.)
		std::vector<InputTuple> nodes;
	public:
		Layer() = delete;
		Layer(noteenums::Note n, 
		      noteenums::Duration d, 
		      std::shared_ptr<NoteMapper<InputTuple>> mapper) : note(n, d) {
			auto range = mapper->getMap().equal_range(n);
			for (auto i = range.first; i != range.second; ++i) {
				if (addNode(i->second) == -1) {
					throw(NodeException<InputTuple>("Failed to add node to layer.\n", 
									i->second, note));
				}
			}		
		}
		Layer(noteenums::Note n, noteenums::Duration d) : note(n, d) {}
		Layer(const SimplifiedNote& n, std::shared_ptr<NoteMapper<InputTuple>> mapper) : note(n) {
			auto range = mapper->getMap().equal_range(note.getNote());
			for (auto i = range.first; i != range.second; ++i) {
				if (addNode(i->second) == -1) {
					throw(NodeException<InputTuple>("Failed to add node to layer.\n", 
									i->second, note));
				}
			}
		}
		~Layer() {}

		//Attempts to add a node to a layer, if node is already present does 
		//nothing and returns -1.
		int addNode(InputTuple n) {
        		const int old_size = nodes.size();
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
		
		//Attempts to remove a node from a layer, returns -1 if failure.
		int removeNode(InputTuple n) {
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

		//Index the nodes
		const InputTuple& operator[](int index) const {
			if (index >= getSize()) {
				throw std::out_of_range("Layer index out of range.");
			}
			return nodes[index];
		}
		int getSize() const {
			return nodes.size();
		}
		void clear() {
			nodes.clear();
		}
		const SimplifiedNote& getNote() const {
			return note;
		}
		const std::vector<InputTuple>& getNodes() const {
			return nodes;
		}
	
};
#endif
