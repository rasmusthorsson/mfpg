#include "mx/api/ScoreData.h"
#include "NoteEnums.h"
#include "ConversionException.h"

using namespace noteenums;

class MXConverter {
	public:
		static Note ConvertNote(mx::api::NoteData);
		static Accidental ConvertAcc(mx::api::NoteData);
		static Duration ConvertDuration(mx::api::NoteData);
};

