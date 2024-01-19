#ifndef HAND_POSITION_H_MFPG
#define HAND_POSITION_H_MFPG

#include "SimplifiedNote.h"

//Output for one layer, a sequence of HandPositions should realistically be the output
//of the program.
//TODO Rename, add more attributes? turn into a list?
template <class InputTuple> class HandPosition {
	private:
		InputTuple state;
		SimplifiedNote note;
	public:
		HandPosition() {}
		HandPosition(InputTuple i) : state(i) {}
		HandPosition(InputTuple i, SimplifiedNote n) : state(i), note(n) {}
		InputTuple getState() {
			return state;
		}
		SimplifiedNote getNote() {
			return note;
		}
}; 
#endif
