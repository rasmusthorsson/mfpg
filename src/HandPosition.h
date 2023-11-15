#include "SimplifiedNote.h"

//Output for one layer
//TODO Rename, add more attributes? turn into a list?
template <class InputTuple> class HandPosition {
	private:
		InputTuple state;
		SimplifiedNote note;
	public:
		HandPosition() {}
		HandPosition(InputTuple i) : state(i) {}
		InputTuple getState() {
			return state;
		}
		SimplifiedNote getNote() {
			return note;
		}
}; 
