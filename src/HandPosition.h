#ifndef HAND_POSITION_H_MFPG
#define HAND_POSITION_H_MFPG

#include "SimplifiedNote.h"
#include "LayerList.h"

//A linked list 
template <class Output> class HandPosition {
	private:
		//Outgoing tuple state
		const PhysAttrMap state;

		//Represented note
		const SimplifiedNote note;

		//Points to the layerlist corresponding to this HandPosition
		const LayerList<Output>& layer_list; 
	public:
		HandPosition() {}
		HandPosition(PhysAttrMap i, LayerList<Output>& ls) : state(i), layer_list(ls) {}
		HandPosition(PhysAttrMap i, SimplifiedNote n, LayerList<Output>& ls) 
						: state(i), note(n), layer_list(ls) {}
		const PhysAttrMap getState() const {
			return state;
		}
		const SimplifiedNote getNote() const {
			return note;
		}
		const LayerList<Output>& getLayerList() const {
			return layer_list;
		}
}; 
#endif
