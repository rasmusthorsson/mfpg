#include "HPSolver.h"

class BasicHPSolver : public virtual HPSolver {
	public:
		BasicHPSolver();
		BasicHPSolver(NoteList* s, NoteMapper* m);
                std::list<int> solve();
};
