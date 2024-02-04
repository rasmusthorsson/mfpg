#ifndef HAND_POSITION_H_MFPG
#define HAND_POSITION_H_MFPG

#include "SimplifiedNote.h"

//A linked list 
template <class InputTuple, class Output> class HandPosition {
	private:
		InputTuple state;
		SimplifiedNote note;
		//Points to the layerlist corresponding to this HandPosition
		LayerList<InputTuple, Output> layer_list; 
	public:
		HandPosition() {}
		HandPosition(InputTuple i, LayerList<InputTuple, Output> ls) 
			: state(i), layer_list(ls) {}
		HandPosition(InputTuple i, SimplifiedNote n, 
				LayerList<InputTuple, Output> ls) 
				: state(i), note(n), layer_list(ls) {}
		InputTuple getState() {
			return state;
		}
		SimplifiedNote getNote() {
			return note;
		}
		LayerList<InputTuple, Output> getLayerList() {
			return layer_list;
		}
}; 
#endif
