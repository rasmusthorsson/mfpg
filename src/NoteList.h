#ifndef NOTE_LIST_H_MFPG
#define NOTE_LIST_H_MFPG

#include <list>
#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"

//Class for representing a score as a list of notes, simpler than mx representation.
class NoteList {
		using it = std::list<SimplifiedNote>::const_iterator;
	private:
		//List of notes in simplified form in the score.
		const std::list<SimplifiedNote> notes;

		//Load notes into the list from the score.
		const std::list<SimplifiedNote> loadNotes(const mx::api::ScoreData&);
	public:
		NoteList() = delete;
		NoteList(const mx::api::ScoreData&);
		
		int size() const;
		
		const SimplifiedNote& front() const;
		const std::list<SimplifiedNote>& getNotes() const;
		const it begin() const;
		const it end() const;
};
#endif
