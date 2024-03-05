#include "HandPosition.h"

template<typename Output>
HandPosition<Output>::HandPosition(PhysAttrMap i, LayerList<Output>& ls) : state(i), layer_list(ls) {}

template<typename Output>
HandPosition<Output>::HandPosition(PhysAttrMap i, SimplifiedNote n, LayerList<Output>& ls) : state(i), note(n), layer_list(ls) {}

template<typename Output>
HandPosition<Output>::HandPosition(PhysAttrMap i, SimplifiedNote n, const LayerList<Output>& ls) : state(i), note(n), layer_list(ls) {}

template<typename Output>
const PhysAttrMap HandPosition<Output>::getState() const {
	return state;
}

template<typename Output>
const SimplifiedNote HandPosition<Output>::getNote() const {
	return note;
}

template<typename Output>
const LayerList<Output>& HandPosition<Output>::getLayerList() const {
	return layer_list;
}
