#ifndef INSTTRUMENT_H_MFPG
#define INSTTRUMENT_H_MFPG

#include "ActionSet.h"
#include <memory>

template <class StateTuple, OutputViable Cost> class Instrument {
	private:
		const std::vector<IString> strings;
		std::shared_ptr<NoteMapper<StateTuple>> note_mapper;
		const std::shared_ptr<ActionSet<StateTuple, Cost>> action_set;
	public:
		Instrument() {}
		Instrument(std::vector<IString> sv, 
			   std::shared_ptr<NoteMapper<StateTuple>> nm, 
			   std::shared_ptr<ActionSet<StateTuple, Cost>> as) : 
			action_set(as), note_mapper(nm), strings(sv) {}
		~Instrument() {}

		const std::shared_ptr<ActionSet<StateTuple, Cost>> getActionSet() const {
			return action_set;
		};
		std::shared_ptr<NoteMapper<StateTuple>> getNoteMapper() const {
			return note_mapper;
		};
		const std::vector<IString>& getStrings() const {
			return strings;
		};
};
#endif
