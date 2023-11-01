#include <list>
#include <iterator>
#include <cstddef>
#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"

//Class for representing a score as a list of notes, simpler than mx implementation.
//TODO Composition over inheritance?
class NoteList {
	private:
		std::list<SimplifiedNote> notes;
		void loadNotes(mx::api::ScoreData score);
	public:
		NoteList() {};
		NoteList(mx::api::ScoreData score);
		int size();
		SimplifiedNote front();
		void pop_front();
		std::list<SimplifiedNote> getNotes();
};
