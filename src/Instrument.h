#ifndef INSTTRUMENT_H_MFPG
#define INSTTRUMENT_H_MFPG

#include "ActionSet.h"

template <class StateTuple, OutputViable Cost> class Instrument {
	private:
		const std::vector<IString> strings;
		NoteMapper<StateTuple>* note_mapper;
		const ActionSet<StateTuple, Cost> action_set;
	public:
		Instrument() {}
		Instrument(std::vector<IString> sv, NoteMapper<StateTuple>* nm, 
					ActionSet<StateTuple, Cost> as) : 
			action_set(as), note_mapper(nm), strings(sv) {}
		~Instrument() {}
		const ActionSet<StateTuple, Cost> getActionSet() const {
			return action_set;
		};
		NoteMapper<StateTuple>* getNoteMapper() const {
			return note_mapper;
		};
		const std::vector<IString> getStrings() const {
			return strings;
		};
};
#endif
