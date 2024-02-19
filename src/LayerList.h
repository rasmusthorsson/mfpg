#ifndef LAYER_LIST_H_MFPG
#define LAYER_LIST_H_MFPG

#include "NoteMapper.h"
#include "Layer.h"
#include "NoteList.h"
#include "ActionSet.h"

#include <iterator>
#include <cstddef>
#include <list>
#include <map>
#include <memory>

//A linked list of layers, each link contains a layer, a pointer to the nect link, and
//a vector of transition costs between the nodes in the current layer and the nodes in
//the next layer
template <class InputTuple, class Output> class LayerList {
	private:
		//Map each tuple in the current layer to an array of values, each 
		//value at position n in the array corresponds to the cost of 
		//transitioning from the mapped tuple to the n'th tuple in the next 
		//layer.
		std::map<InputTuple, std::vector<Output>> transitions;
		//Layers are to be owned by the respective LayerList node.
		Layer<InputTuple> elem;
		LayerList<InputTuple, Output>* next = NULL;

		//Functions used for testing only
		void pushBack(Layer<InputTuple> layer) {
			if (next == NULL) {
				setNext(layer);
			} else {
				next->pushBack(layer);
			}
		}
		int setNext(Layer<InputTuple> layer) {
			if (next != NULL) {
				return -1;
			}
			next = new LayerList<InputTuple, Output>(layer);
			return 1;
		}
	public:
		LayerList() {}

		//Constructors for tests only -----------
		LayerList(Layer<InputTuple> l) : elem(l) {}
		LayerList(std::vector<Layer<InputTuple>> ls) : elem(ls[0]) {
			for (int i = 1; i < ls.size(); i++) {
				pushBack(ls[i]);
			}
		}
		//---------------------------------------

		LayerList(const SimplifiedNote& s, std::shared_ptr<NoteMapper<InputTuple>> note_mapper)
			: elem(s, note_mapper) {}
		LayerList(const NoteList& list, std::shared_ptr<NoteMapper<InputTuple>> note_mapper) : 
				elem(list.front(), note_mapper) {
			auto it = list.begin();
			for (++it; it != list.end(); it++) {
				pushBack(*it, note_mapper);
			}	
		}
		~LayerList() {
			if (next != NULL) {
				delete next;
			}
		}
		int setNext(LayerList<InputTuple, Output>* l) {
			if (next != NULL) {
				return -1;
			}
			next = l;
			return 1;
		}
		int setNext(const SimplifiedNote& s, std::shared_ptr<NoteMapper<InputTuple>> note_mapper) {
			if (next != NULL) {
				return -1;
			}
			next = new LayerList<InputTuple, Output>(s, note_mapper);
			return 1;
		}
		const LayerList<InputTuple, Output>* getNext() const {
			return next;
		}
		void pushBack(const SimplifiedNote& s, std::shared_ptr<NoteMapper<InputTuple>> note_mapper) {
			if (next == NULL) {
				setNext(s, note_mapper);
			} else {
				next->pushBack(s, note_mapper);
			}
		}
		const Layer<InputTuple>& getElem() const {
			return elem;
		}
		int getSize() const {
			return elem.getSize();
		}
		int buildTransitions(const std::shared_ptr<ActionSet<InputTuple, Output>> as) {
			if (next == NULL) {
				return 1;
			}
			auto next_layer = next->getElem();
			for (const InputTuple& this_tuple : elem) {
				std::vector<Output> outputs;
				for (const InputTuple& next_tuple : next_layer) {
					outputs.push_back(
						as->apply(this_tuple, next_tuple));
				}
				transitions.insert({this_tuple, outputs});
			} 
			return next->buildTransitions(as);
		}
		std::map<InputTuple, std::vector<Output>>& getTransitions() {
			return transitions;
		}
		//Iterator
		//TODO const iterator
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = LayerList<InputTuple, Output>;
			using pointer = LayerList<InputTuple, Output>*;
			using reference = LayerList<InputTuple, Output>&;
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
			return Iterator(this);
		}
		Iterator end() {
			return Iterator(NULL);
		}
};	
#endif
