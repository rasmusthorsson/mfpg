#include "Action.h"
#include <list>
#include <map>
#include "Layer.h"
#include "LayerListException.h"
#include <iterator>
#include <cstddef>

template <class T, class C> class LayerList {
	private:
		//Map each tuple in the current layer to an array of values, each value at position
		//n in the array corresponds to the cost of transitioning from the mapped tuple
		//to the n'th tuple in the next layer.
		std::map<T, std::vector<C>> transitions;
		Layer<T> elem;
		LayerList<T, C>* prev = NULL;
		LayerList<T, C>* next = NULL;
	public:
		LayerList(Layer<T> l) : elem(l) {}
		void setPrev(LayerList<T, C>* l, Action<T, C> a) {
			if (l->next != NULL) {
//				throw LayerListException
//					("Previous node already has a next node.", false, l);	
			}
			prev = l;
			//l->setNext(this, a);
		}
		void setNext(LayerList<T, C>* l, Action<T, C> a) {
			if (next->prev != NULL) {
//				throw LayerListException
//					("Next node already has a previous node.", true, l);
			}
			next = l;
			//l->setPrev(this, a);
		}
		Layer<T> getElem() {
			return elem;
		}
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = LayerList<T, C>;
			using pointer = LayerList<T, C>*;
			using reference = LayerList<T, C>&;
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
			return Iterator(next);
		}
};	
