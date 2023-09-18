#include "BasicHPSolver.h"

BasicHPSolver::BasicHPSolver() {}
BasicHPSolver::BasicHPSolver(NoteList* s, NoteMapper* m) {
	setScore(s);
	setNoteMap(m);
}


std::list<int> BasicHPSolver::solve() {
	return std::list<int>{1};
}

