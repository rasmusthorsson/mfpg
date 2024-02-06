#ifndef INSTTRUMENT_H_MFPG
#define INSTTRUMENT_H_MFPG

#include "ActionSet.h"

template <class StateTuple, OutputViable Cost> class Instrument {
	private:
		std::vector<IString> strings;
		NoteMapper<StateTuple>* note_mapper;
		ActionSet<StateTuple, Cost> action_set;
	public:
		Instrument() {}
		Instrument(std::vector<IString> sv, NoteMapper<StateTuple>* nm, 
					ActionSet<StateTuple, Cost> as) : 
			action_set(as), note_mapper(nm), strings(sv) {}
		~Instrument() {}
		ActionSet<StateTuple, Cost> getActionSet(){
			return action_set;
		};
		NoteMapper<StateTuple>* getNoteMapper() {
			return note_mapper;
		};
		std::vector<IString> getStrings() {
			return strings;
		};
};
#endif
