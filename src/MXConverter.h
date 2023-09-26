#include "mx/api/ScoreData.h"
#include "NoteEnums.h"
#include "ConversionException.h"

using namespace noteenums;

//Used to convert mx notes to noteenums notes.
class MXConverter {
	public:
		static Note ConvertNote(mx::api::NoteData);
		static Duration ConvertDuration(mx::api::NoteData);
};

