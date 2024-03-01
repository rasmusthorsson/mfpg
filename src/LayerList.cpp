#include "LayerList.h"

template<typename Output>
void LayerList<Output>::pushBack(Layer layer) {
	if (next == NULL) {
		if (setNext(layer) == -1) {
			throw (LinkException<Output>("Failed to set next link"));
		}
	} else {
		next->pushBack(layer);
	}
}

template<typename Output>
int LayerList<Output>::setNext(Layer layer) {
	if (next != NULL) {
		return -1;
	}
	next = new LayerList<Output>(layer);
	return 1;
}

template<typename Output>
LayerList<Output>::LayerList() {}

template<typename Output>
LayerList<Output>::LayerList(Layer l) : elem(l) {}

template<typename Output>
LayerList<Output>::LayerList(std::vector<Layer> ls) : elem(ls[0]) {
	for (int i = 1; i < ls.size(); i++) {
		pushBack(ls[i]);
	}
}

template<typename Output>
LayerList<Output>::LayerList(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper)
	: elem(s, note_mapper) {} 

template<typename Output>
LayerList<Output>::LayerList(const NoteList& list, std::shared_ptr<NoteMapper> note_mapper) : 
		elem(list.front(), note_mapper) {
	auto it = list.getNotes().begin();
	for (++it; it != list.getNotes().end(); it++) {
		pushBack(*it, note_mapper);
	}	
}

template<typename Output>
LayerList<Output>::~LayerList() {
	if (next != NULL) {
		delete next;
	}
}

template<typename Output>
int LayerList<Output>::setNext(LayerList<Output>* l) {
	if (next != NULL) {
		return -1;
	}
	next = l;
	return 1;
}

template<typename Output>
int LayerList<Output>::setNext(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper) {
	if (next != NULL) {
		return -1;
	}
	next = new LayerList<Output>(s, note_mapper);
	return 1;
}

template<typename Output>
const LayerList<Output>* LayerList<Output>::getNext() const {
	return next;
}

template<typename Output>
void LayerList<Output>::pushBack(const SimplifiedNote& s, std::shared_ptr<NoteMapper> note_mapper) {
	if (next == NULL) {
		if (setNext(s, note_mapper) == -1) {
			throw (LinkException<Output> ("Failed to set next link"));
		}
	} else {
		next->pushBack(s, note_mapper);
	}
}

template<typename Output>
const Layer& LayerList<Output>::getElem() const {
	return elem;
}

template<typename Output>
int LayerList<Output>::getSize() const {
	return elem.getSize();
}

template<typename Output>
int LayerList<Output>::buildTransitions(const std::shared_ptr<ActionSet<Output>> as) {
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

template<typename Output>
std::map<PhysAttrMap, std::vector<Output>, PhysAttrMap::AttrLess>& LayerList<Output>::getTransitions() {
	return transitions;
}
