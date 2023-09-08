#include <gtest/gtest.h>
#include "SimplifiedNote.h"
#include "ConversionException.h"

TEST(SimplifiedNote, ValidInputs) {
	using namespace mx::api;
	using namespace simplifiednote;
	NoteData note = NoteData{};
	note.durationData.durationName = DurationName::whole;
	note.pitchData.step = Step::d;
	SimplifiedNote simpleNote(note);
	EXPECT_EQ(noteenums::Note::D, simpleNote.getNote());
}

TEST(SimplifiedNote, Uninitialized) {
	using namespace mx::api;
	using namespace simplifiednote;
	NoteData note = NoteData{};
	ASSERT_THROW(SimplifiedNote simpleNote(note), ConversionException);
	try {
		SimplifiedNote simpleNote(note);
	} catch (ConversionException ce) {
		EXPECT_EQ(ce.err(), "Duration not found.");
	}
}
