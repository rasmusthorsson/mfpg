#ifndef HAND_POSITION_H_MFPG
#define HAND_POSITION_H_MFPG

#include "SimplifiedNote.h"
#include "LayerList.h"

//A linked list 
template <class InputTuple, class Output> class HandPosition {
	private:
		//Outgoing tuple state
		const InputTuple state;

		//Represented note
		const SimplifiedNote note;

		//Points to the layerlist corresponding to this HandPosition
		const LayerList<InputTuple, Output>& layer_list; 
	public:
		HandPosition() {}
		HandPosition(InputTuple i, LayerList<InputTuple, Output>& ls) : state(i), layer_list(ls) {}
		HandPosition(InputTuple i, SimplifiedNote n, LayerList<InputTuple, Output>& ls) 
						: state(i), note(n), layer_list(ls) {}
		const InputTuple getState() const {
			return state;
		}
		const SimplifiedNote getNote() const {
			return note;
		}
		const LayerList<InputTuple, Output>& getLayerList() const {
			return layer_list;
		}
}; 
#endif
