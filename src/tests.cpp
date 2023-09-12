#include <gtest/gtest.h>
#include "SimplifiedNote.h"
#include "ConversionException.h"

TEST(SimplifiedNote, ValidInputs) {
	using namespace mx::api;
	using namespace simplifiednote;
	NoteData note = NoteData{};
	note.durationData.durationName = DurationName::whole;
	note.pitchData.step = Step::d;
	note.pitchData.octave = 3;
	note.pitchData.alter = 1;
	SimplifiedNote simpleNote(note);
	EXPECT_EQ(noteenums::Note::Ds_3, simpleNote.getNote());
}

TEST(SimplifiedNote, NoteTooHigh) {
	using namespace mx::api;
	using namespace simplifiednote;
	NoteData note = NoteData{};
	note.durationData.durationName = DurationName::whole;
	note.pitchData.step = Step::b;
	note.pitchData.octave = 8;
	note.pitchData.alter = 5;
	ASSERT_THROW(SimplifiedNote simpleNote(note), ConversionException);
	try {
		SimplifiedNote simpleNote(note);
	} catch (ConversionException ce) {
		EXPECT_EQ(ce.err(), "Note out of range.");
	}	
}	

TEST(SimplifiedNote, NoteTooLow) {
	using namespace mx::api;
	using namespace simplifiednote;
	NoteData note = NoteData{};
	note.durationData.durationName = DurationName::whole;
	note.pitchData.step = Step::c;
	note.pitchData.octave = 0;
	note.pitchData.alter = -2;
	ASSERT_THROW(SimplifiedNote simpleNote(note), ConversionException);
	try {
		SimplifiedNote simpleNote(note);
	} catch (ConversionException ce) {
		EXPECT_EQ(ce.err(), "Note out of range.");
	}	
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
