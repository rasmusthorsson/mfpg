#include "Action.h"
#include <list>
#include <map>
#include "Layer.h"
#include "LayerListException.h"

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
		void setPrev(LayerList<T, C>* l, C (*dist_fun(T, T))) {
			if (l.next != NULL) {
				throw LayerListException("Previous node already has a next node.",
					false, l);	
			}
			prev = l;
			l.setNext(*this);
		}
		void setNext(LayerList<T, C>* l, C (*dist_fun)(T, T)) {
			if (next.prev != NULL) {
				throw LayerListException("Next node already has a previous node.",
						true, l);
			}
			next = l;
			l.setPrev(*this);
		}
		Layer<T> getElem() {
			return elem;
		}
};	
