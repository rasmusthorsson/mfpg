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
		void pushBack(Layer layer);
		int setNext(Layer layer);
	public:
		LayerList();

		//Constructors for tests only -----------
		LayerList(Layer l);
		LayerList(std::vector<Layer> ls);
		
		//---------------------------------------
		LayerList(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper); 
		LayerList(const NoteList& list, std::shared_ptr<NoteMapper> note_mapper);
		~LayerList(); 
	
		//Set next, fails if next is already set.
		int setNext(LayerList<Output>* l);
		
		//Set next, fails if next is already set.
		int setNext(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper);

		const LayerList<Output>* getNext() const;

		//Push new layerlist to the end of the list.
		void pushBack(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper);

		const Layer& getElem() const;

		int getSize() const;

		//Builds transitions through the entire layerlist using an actionset.
		int buildTransitions(const std::shared_ptr<ActionSet<Output>> as);

		std::map<PhysAttrMap, std::vector<Output>, PhysAttrMap::AttrLess>& getTransitions();

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
