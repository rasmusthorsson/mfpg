#ifndef LAYER_LIST_H_MFPG
#define LAYER_LIST_H_MFPG

#include <list>
#include <map>
#include "Layer.h"
#include "NoteList.h"
#include "ActionSet.h"
#include <iterator>
#include <cstddef>

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
		Layer<InputTuple> elem;
		LayerList<InputTuple, Output>* next = NULL;
	public:
		LayerList() {}
		LayerList(Layer<InputTuple> l) : elem(l) {}
		LayerList(NoteList list) : elem(list.front()) {
			std::list<SimplifiedNote> simpList = list.getNotes();
			auto it = simpList.begin();
			it++;
			for (it; it != simpList.end(); it++) {
				Layer<InputTuple>* temp = new Layer<InputTuple>(*it);
				this->pushBack(*temp);
			}	
		}
		LayerList(std::vector<Layer<InputTuple>> ls) 
			: elem(ls[0]) {
			LayerList<InputTuple, Output>* base = this;
			for (int i = 1; i < ls.size(); i++) {
				LayerList<InputTuple, Output>* temp = 
					new LayerList<InputTuple, Output>(ls[i]);
				base->setNext(temp);
				base = temp;
			}
		}
		void setNext(LayerList<InputTuple, Output>* l) {
			next = l;
		}
		void setNext(Layer<InputTuple> layer) {
			LayerList<InputTuple, Output>* temp = 
				new LayerList<InputTuple, Output>(layer);
			next = temp;
		}
		LayerList<InputTuple, Output>* getNext() {
			return next;
		}
		void pushBack(Layer<InputTuple> layer) {
			auto current = this;
			while (current->getNext() != NULL) {
				current = current->getNext();
			}
			current->setNext(layer);
		}
		Layer<InputTuple> getElem() {
			return elem;
		}
		int getSize() {
			return elem.getSize();
		}
		int buildTransitions(ActionSet<InputTuple, Output> as) {
			if (next == NULL) {
				return 1;
			}
			for (InputTuple thisTuple : elem) {
				std::vector<Output> outputs;
				for (InputTuple nextTuple : next->getElem()) {
					outputs.push_back(
						as.apply(thisTuple, nextTuple));
				}
				transitions.insert({thisTuple, outputs});
			} 
			return next->buildTransitions(as);
		}
		std::map<InputTuple, std::vector<Output>> getTransitions() {
			return transitions;
		}
		//Iterator
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using valT = LayerList<InputTuple, Output>;
			using pointer = LayerList<InputTuple, Output>*;
			using reference = LayerList<InputTuple, Output>&;
			private:
				pointer ptr;
			public:
				Iterator(pointer ptr) : ptr(ptr) {}
				reference operator*() const {return *ptr;}
				pointer operator->() {return ptr;}

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
