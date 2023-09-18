#include <list>
#include "NoteList.h"
#include "NoteMapper.h"

class HPSolver {
	protected:
		NoteList* score;
		NoteMapper* notemap;
	public:
		HPSolver() {};
		virtual std::list<int> solve() = 0;
		virtual void setScore(NoteList* s) {score = s;};
		virtual void setNoteMap(NoteMapper* m) {notemap = m;};
		virtual NoteList* getScore() {return score;};
		virtual NoteMapper* getNoteMap() {return notemap;};
};
