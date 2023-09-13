#include <vector>
#include "SimplifiedNote.h"

class IString {
	private:
		const int position;
		const std::vector<simplifiednote::SimplifiedNote> playableNotes;
	public:
		IString(int p, std::vector<simplifiednote::SimplifiedNote> n);
		int getPosition();
		std::vector<simplifiednote::SimplifiedNote> getPlayable();
		simplifiednote::SimplifiedNote getNote(int i);
};
