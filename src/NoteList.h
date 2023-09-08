#include <list>
#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"

class NoteList : public std::list<simplifiednote::SimplifiedNote> {

	private:
		void loadNotes(mx::api::ScoreData score);
	public:
		NoteList(mx::api::ScoreData score);
};
