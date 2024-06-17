#ifndef NOTE_LIST_H_MFPG
#define NOTE_LIST_H_MFPG

#include <list>
#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"

//Class for representing a score as a list of notes, simpler than mx representation.
class NoteList {
	private:
		//List of notes in simplified form in the score.
		std::list<SimplifiedNote> notes;

	public:
		NoteList();
		NoteList(const mx::api::ScoreData&);
		
		int size() const;
		//Load notes into the list from the score.
		const void loadNotes(const mx::api::ScoreData&);
		
		const SimplifiedNote& front() const;
		const std::list<SimplifiedNote>& getNotes() const;
};
#endif
