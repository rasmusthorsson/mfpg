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
template <typename Output> class LayerList {
	private:
		//Matrix of outputs, the rows represent current physical representation nodes, while the
		//columns represent the next layers nodes. The values in the matrix are the costs for
		//each transition.
		std::vector<std::vector<Output>> transitions;
		//Layers are to be owned by the respective LayerList node.
		Layer elem;
		//Next link in list.
		LayerList<Output>* next = NULL;

		//Functions used for testing only
		void pushBack(Layer);
		int setNext(Layer);
	public:
		//Constructors for tests only
		LayerList(Layer l);
		LayerList(std::vector<Layer> ls);
		
		//---------------------------------------
		LayerList();
		LayerList(const SimplifiedNote&, std::shared_ptr<NoteMapper>); 
		LayerList(const NoteList&, std::shared_ptr<NoteMapper>);
		~LayerList(); 
	
		//Set next, fails if next is already set.
		int setNext(LayerList<Output>*);
		//Set next, fails if next is already set.
		int setNext(const SimplifiedNote&, std::shared_ptr<NoteMapper>);
		//Push new layerlist to the end of the list.
		void pushBack(const SimplifiedNote&, std::shared_ptr<NoteMapper>);
		
		const LayerList<Output>* getNext() const;
		const Layer& getElem() const;

		//Gets size of layerlist until NULL pointer is reached.
		int getSize();
		//Gets the list in the n'th link, where n is the parameter (from 0).
		const LayerList<Output>& getList(int) const;
		const std::vector<std::vector<Output>>& getTransitions() const;
		std::vector<std::vector<Output>> copyTransitions();
		
		//Builds transitions through the entire layerlist using an actionset.
		int buildTransitions(const std::shared_ptr<ActionSet<Output>>);

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
