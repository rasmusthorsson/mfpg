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
		Layer() {}
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
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = NodeTuple;
			using pointer = val_t*;
			using reference = val_t&;
			private:
				pointer m_ptr;
			public:
				Iterator(pointer ptr) : m_ptr(ptr) {}
				reference operator*() const {return *m_ptr;}
				pointer operator->() {return m_ptr;}

				Iterator& operator++() {
					m_ptr++;
					return *this;
				}
				Iterator operator++(int) {
					pointer prev = m_ptr;
					m_ptr++;
					return Iterator(prev);
				}

				friend bool operator==(const Iterator& fst, const Iterator& snd) {
					return fst.m_ptr == snd.m_ptr;
				}
				friend bool operator!=(const Iterator& fst, const Iterator& snd) {
					return fst.m_ptr != snd.m_ptr;
				}
		};

		Iterator begin() {
			return Iterator(&nodes[0]);
		}
		Iterator end() {
			return Iterator(&nodes[nodes.size()]);
		}
};
