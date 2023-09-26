#include <list>
#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"

//Class for representing a score as a list of notes, simpler than mx implementation.
class NoteList : public std::list<simplifiednote::SimplifiedNote> {
	private:
		void loadNotes(mx::api::ScoreData score);
	public:
		NoteList() {};
		NoteList(mx::api::ScoreData score);
};
