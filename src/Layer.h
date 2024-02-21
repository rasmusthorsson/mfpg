#ifndef LAYER_H_MFPG
#define LAYER_H_MFPG

#include "SimplifiedNote.h"
#include "NodeException.h"
#include "NoteEnums.h"
#include "NoteMapper.h"

#include <memory>
#include <vector>
#include <cassert>

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
			auto range = mapper->getRange(n);
			for (auto i = range.first; i != range.second; ++i) {
				if (addNode(i->second) == -1) {
					throw(NodeException<InputTuple>("Failed to add node to layer.\n", 
									i->second, note));
				}
			}		
		}
		Layer(noteenums::Note n, noteenums::Duration d) : note(n, d) {}
		Layer(const SimplifiedNote& n, std::shared_ptr<NoteMapper<InputTuple>> mapper) : note(n) {
			auto range = mapper->getRange(note.getNote());
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
		
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = InputTuple;
			using pointer = val_t*;
			using reference = val_t&;
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
				friend bool operator==(const Iterator& fst, const Iterator& snd) {
					return fst.ptr == snd.ptr;
				}
				friend bool operator!=(const Iterator& fst, const Iterator& snd) {
					return fst.ptr != snd.ptr;
				}
		};
		Iterator begin() {
			return Iterator(&nodes[0]);
		}
		Iterator end() {
			return Iterator(&nodes[0] + nodes.size());
		}
};
#endif
