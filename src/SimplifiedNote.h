#include "NoteEnums.h"
#include "mx/api/ScoreData.h"

using namespace noteenums;

namespace simplifiednote {

class SimplifiedNote {
	private:
		const Note note;
		const Accidental acc;
		const Duration duration;

	public:
		SimplifiedNote(mx::api::NoteData);
		~SimplifiedNote();
		Note getNote();
		Accidental getAcc();
		Duration getDuration();
};

}
