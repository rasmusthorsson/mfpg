#ifndef INSTTRUMENT_H_MFPG
#define INSTTRUMENT_H_MFPG

#include "ActionSet.h"

template <class StateTuple, OutputViable Weight> class Instrument {
	private:
		ActionSet<StateTuple, Weight> actions;
		NoteMapper<StateTuple>* notemapper;
		std::vector<IString> strings;
	public:
		Instrument() {}
		Instrument(ActionSet<StateTuple, Weight> as, 
				NoteMapper<StateTuple>* nm, std::vector<IString> sv) : 
			actions(as), notemapper(nm), strings(sv) {}
};
#endif
