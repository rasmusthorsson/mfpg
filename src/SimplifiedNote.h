#include "NoteEnums.h"
#include "mx/api/ScoreData.h"

using namespace noteenums;

namespace simplifiednote {

class SimplifiedNote {
	private:
		const Note note;
		const Duration duration;

	public:
		SimplifiedNote(mx::api::NoteData);
		~SimplifiedNote();
		Note getNote();
		Duration getDuration();
		bool operator <(const SimplifiedNote &rhs) const {
			return (note < rhs.note);
		}
};

}
