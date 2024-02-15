#ifndef NOTE_LIST_H_MFPG
#define NOTE_LIST_H_MFPG

#include <list>
#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"

//Class for representing a score as a list of notes, simpler than mx representation.
class NoteList {
		using it = std::list<SimplifiedNote>::const_iterator;
	private:
		const std::list<SimplifiedNote> notes;
		const std::list<SimplifiedNote> loadNotes(mx::api::ScoreData);
	public:
		NoteList() {};
		NoteList(mx::api::ScoreData);
		int size() const;
		const SimplifiedNote front() const;
		const std::list<SimplifiedNote> getNotes() const;
		it begin() const;
};
#endif
