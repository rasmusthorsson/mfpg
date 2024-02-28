#ifndef LAYER_LIST_H_MFPG
#define LAYER_LIST_H_MFPG

#include "NoteMapper.h"
#include "Layer.h"
#include "NoteList.h"
#include "ActionSet.h"
#include "LinkException.h"
#include "PhysAttrMap.h"

#include <iterator>
#include <cstddef>
#include <list>
#include <map>
#include <memory>

//A linked list of layers, each link contains a layer, a pointer to the nect link, and
//a vector of transition costs between the nodes in the current layer and the nodes in
//the next layer
template <class Output> class LayerList {
	private:
		//Map each tuple in the current layer to an array of values, each 
		//value at position n in the array corresponds to the cost of 
		//transitioning from the mapped tuple to the n'th tuple in the next 
		//layer.
		std::map<PhysAttrMap, std::vector<Output>, PhysAttrMap::AttrLess> transitions;

		//Layers are to be owned by the respective LayerList node.
		Layer elem;
		//Next link in list.
		LayerList<Output>* next = NULL;

		//Functions used for testing only
		void pushBack(Layer layer) {
			if (next == NULL) {
				if (setNext(layer) == -1) {
					throw (LinkException<Output>("Failed to set next link"));
				}
			} else {
				next->pushBack(layer);
			}
		}
		int setNext(Layer layer) {
			if (next != NULL) {
				return -1;
			}
			next = new LayerList<Output>(layer);
			return 1;
		}
	public:
		LayerList() {}

		//Constructors for tests only -----------
		LayerList(Layer l) : elem(l) {}
		LayerList(std::vector<Layer> ls) : elem(ls[0]) {
			for (int i = 1; i < ls.size(); i++) {
				pushBack(ls[i]);
			}
		}
		//---------------------------------------

		LayerList(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper)
			: elem(s, note_mapper) {} 
		LayerList(const NoteList& list, std::shared_ptr<NoteMapper> note_mapper) : 
				elem(list.front(), note_mapper) {
			auto it = list.getNotes().begin();
			for (++it; it != list.getNotes().end(); it++) {
				pushBack(*it, note_mapper);
			}	
		}
		~LayerList() {
			if (next != NULL) {
				delete next;
			}
		}

		//Set next, fails if next is already set.
		int setNext(LayerList<Output>* l) {
			if (next != NULL) {
				return -1;
			}
			next = l;
			return 1;
		}
		//Set next, fails if next is already set.
		int setNext(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper) {
			if (next != NULL) {
				return -1;
			}
			next = new LayerList<Output>(s, note_mapper);
			return 1;
		}

		const LayerList<Output>* getNext() const {
			return next;
		}

		//Push new layerlist to the end of the list.
		void pushBack(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper) {
			if (next == NULL) {
				if (setNext(s, note_mapper) == -1) {
					throw (LinkException<Output> ("Failed to set next link"));
				}
			} else {
				next->pushBack(s, note_mapper);
			}
		}

		const Layer& getElem() const {
			return elem;
		}

		int getSize() const {
			return elem.getSize();
		}

		//Builds transitions through the entire layerlist using an actionset.
		int buildTransitions(const std::shared_ptr<ActionSet<Output>> as) {
			if (next == NULL) {
				return 1;
			}
			auto next_layer = next->getElem();
			for (const PhysAttrMap& this_tuple : elem.getNodes()) {
				std::vector<Output> outputs;
				for (const PhysAttrMap& next_tuple : next_layer.getNodes()) {
					outputs.push_back(as->apply(this_tuple, next_tuple));
				}
				bool l = transitions.insert(std::make_pair(this_tuple, outputs)).second;
			} 
			return next->buildTransitions(as);
		}

		std::map<PhysAttrMap, std::vector<Output>, PhysAttrMap::AttrLess>& getTransitions() {
			return transitions;
		}

		//Iterator
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = LayerList<Output>;
			using pointer = LayerList<Output>*;
			using reference = LayerList<Output>&;
			private:
				pointer ptr;
			public:
				Iterator(pointer ptr) : ptr(ptr) {}
				reference operator*() const {return *ptr;}
				pointer operator->() const {return ptr;}

				Iterator& operator++() {
					ptr = ptr->next;
					return *this;
				}
				Iterator operator++(int) {
					pointer prev = ptr;
					ptr = ptr->next;
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
			return Iterator(this);
		}
		Iterator end() {
			return Iterator(NULL);
		}
};	
#endif
