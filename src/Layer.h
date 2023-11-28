#include "SimplifiedNote.h"
#include "NodeException.h"
#include <vector>
#include <cassert>
#include "NoteEnums.h"

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
		Layer() {}
		Layer(noteenums::Note n, noteenums::Duration d, 
					NoteMapper<InputTuple>* mapper) : note(n, d) {
			auto range = mapper->getRange(n);
			for (auto i = range.first; i != range.second; ++i) {
				addNode(i->second);
			}		
		}
		Layer(noteenums::Note n, noteenums::Duration d) : note(n, d) {}
		Layer(SimplifiedNote n) : note(n), nodes() {}
		Layer(SimplifiedNote n, NoteMapper<InputTuple>* mapper) : note(n) {
			auto range = mapper->getRange(n.getNote());
			for (auto i = range.first; i != range.second; ++i) {
				addNode(i->second);
			}
		}
		//Attempts to add a node to a layer, if node is already present does 
		//nothing and returns -1.
		int addNode(InputTuple n) {
        		int oldSize = nodes.size();
        		for (auto i = nodes.begin(); i != nodes.end(); i++) {
				if (n == *i) {
					return -1;
				}
			}
			nodes.push_back(n);
        		if (!(nodes.size() == oldSize + 1)) {
        			return -1;
			}
			return 1;
		}
		
		//Attempts to remove a node from a layer, throws exception if node is 
		//no present.
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
		std::vector<InputTuple> getNodes() {
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
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using valT = InputTuple;
			using pointer = valT*;
			using reference = valT&;
			private:
				pointer ptr;
			public:
				Iterator(pointer ptr) : ptr(ptr) {}
				reference operator*() const {return *ptr;}
				pointer operator->() {return ptr;}

				Iterator& operator++() {
					ptr++;
					return *this;
				}
				Iterator operator++(int) {
					pointer prev = ptr;
					ptr++;
					return Iterator(prev);
				}

				friend bool operator==(const Iterator& fst, 
								const Iterator& snd) {
					return fst.ptr == snd.ptr;
				}
				friend bool operator!=(const Iterator& fst, 
								const Iterator& snd) {
					return fst.ptr != snd.ptr;
				}
		};

		Iterator begin() {
			return Iterator(&nodes[0]);
		}
		Iterator end() {
			return Iterator(&nodes[nodes.size()]);
		}
};
