#ifndef MX_CONVERTER_H_MFPG
#define MX_CONVERTER_H_MFPG

#include "mx/api/ScoreData.h"
#include "NoteEnums.h"
#include "ConversionException.h"

using namespace noteenums;

//Used to convert mx notes to noteenums notes.
class MXConverter {
	public:
		//Convert notedata to Note.
		static const Note ConvertNote(mx::api::NoteData&);

		//Convert notedata to duration.
		static const Duration ConvertDuration(mx::api::NoteData&);
};
#endif
