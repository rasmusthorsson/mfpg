#include "Action.h"
#include <list>
#include <map>
#include "Layer.h"
#include "LayerListException.h"
#include <iterator>
#include <cstddef>

template <class InputTuple, class Output> class LayerList {
	private:
		//Map each tuple in the current layer to an array of values, each value at position
		//n in the array corresponds to the cost of transitioning from the mapped tuple
		//to the n'th tuple in the next layer.
		std::map<InputTuple, std::vector<Output>> transitions;
		Layer<InputTuple> elem;
		LayerList<InputTuple, Output>* next = NULL;
	public:
		LayerList(Layer<InputTuple> l) : elem(l) {}
		LayerList(std::vector<Layer<InputTuple>> ls, Action<InputTuple, Output> a) 
			: elem(ls[0]) {
			LayerList<InputTuple, Output>* base = this;
			for (int i = 1; i < ls.size(); i++) {
				LayerList<InputTuple, Output>* temp = 
					new LayerList<InputTuple, Output>(ls[i]);
				base->setNext(temp, a);
				base = temp;
			}
		}
		//TODO Set up action to calculate transitions.
		void setNext(LayerList<InputTuple, Output>* l, Action<InputTuple, Output> a) {
			next = l;
		}
		Layer<InputTuple> getElem() {
			return elem;
		}
		LayerList<InputTuple, Output>* getNext() {return next;}
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = LayerList<InputTuple, Output>;
			using pointer = LayerList<InputTuple, Output>*;
			using reference = LayerList<InputTuple, Output>&;
			private:
				pointer m_ptr;
			public:
				Iterator(pointer ptr) : m_ptr(ptr) {}
				reference operator*() const {return *m_ptr;}
				pointer operator->() {return m_ptr;}

				Iterator& operator++() {
					m_ptr = m_ptr->next;
					return *this;
				}

				friend bool operator==(const Iterator& fst, const Iterator& snd) {
					return fst.m_ptr == snd.m_ptr;
				}
				friend bool operator!=(const Iterator& fst, const Iterator& snd) {
					return fst.m_ptr != snd.m_ptr;
				}
		};

		Iterator begin() {
			return Iterator(this);
		}
		Iterator end() {
			return Iterator(NULL);
		}
};	
