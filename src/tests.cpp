#include <gtest/gtest.h>
#include "ConversionException.h"
#include "NoteList.h"
#include "NoteMapper.h"

//Tests valid construction of a simplified note.
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

//Tests construction of a note higher than the allowed range of notes.
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

//Tests construction of a note lower than the allowed range of notes.
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

//Tests construction of an undefined note.
TEST(SimplifiedNote, Undefined) {
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

//Tests an empty NoteList is the result of an empty score.
TEST(NoteList, Undefined) {
	using namespace mx::api;
	ScoreData score = ScoreData{};
	NoteList noteList(score);
	ASSERT_EQ(noteList.size(), 0);
}

class NoteMapper_Tests : public ::testing::Test {
	private:
		std::pair<IString, IString> createStrings() {
			using namespace std;
			using namespace simplifiednote;
			using namespace mx::api;
			NoteData C = NoteData{};
			C.durationData.durationName = DurationName::whole;
			C.pitchData.step = Step::c;
			C.pitchData.octave = 3;
			C.pitchData.alter = 0;
			NoteData C_s = NoteData{};
			C_s.durationData.durationName = DurationName::whole;
			C_s.pitchData.step = Step::c;
			C_s.pitchData.octave = 3;
			C_s.pitchData.alter = 1;
			NoteData D = NoteData{};
			D.durationData.durationName = DurationName::whole;
			D.pitchData.step = Step::d;
			D.pitchData.octave = 3;
			D.pitchData.alter = 0;
			NoteData D_s = NoteData{};
			D_s.durationData.durationName = DurationName::whole;
			D_s.pitchData.step = Step::d;
			D_s.pitchData.octave = 3;
			D_s.pitchData.alter = 1;
			NoteData E = NoteData{};
			E.durationData.durationName = DurationName::whole;
			E.pitchData.step = Step::e;
			E.pitchData.octave = 3;
			E.pitchData.alter = 0;
			NoteData F = NoteData{};
			F.durationData.durationName = DurationName::whole;
			F.pitchData.step = Step::f;
			F.pitchData.octave = 3;
			F.pitchData.alter = 0;
			NoteData F_s = NoteData{};
			F_s.durationData.durationName = DurationName::whole;
			F_s.pitchData.step = Step::f;
			F_s.pitchData.octave = 3;
			F_s.pitchData.alter = 1;
			NoteData G = NoteData{};
			G.durationData.durationName = DurationName::whole;
			G.pitchData.step = Step::g;
			G.pitchData.octave = 3;
			G.pitchData.alter = 0;
			NoteData G_s = NoteData{};
			G_s.durationData.durationName = DurationName::whole;
			G_s.pitchData.step = Step::g;
			G_s.pitchData.octave = 3;
			G_s.pitchData.alter = 1;
			SimplifiedNote SC(C);
			SimplifiedNote SC_s(C_s);
			SimplifiedNote SD(D);
			SimplifiedNote SD_s(D_s);
			SimplifiedNote SE(E);
			SimplifiedNote SF(F);
			SimplifiedNote SF_s(F_s);
			SimplifiedNote SG(G);
			SimplifiedNote SG_s(G_s);
			std::vector<simplifiednote::SimplifiedNote> 
				notes_1{SC, SC_s, SD, SD_s, SE, SF};
			std::vector<simplifiednote::SimplifiedNote> 
				notes_2{SD_s, SE, SF, SF_s, SG, SG_s};
			IString s1(1, notes_1);
			IString s2(2, notes_2);
			return make_pair(s1, s2);
		}
	public:
	       	NoteMapper_Tests() : s1(createStrings().first), s2(createStrings().second) {}
		const IString s1;
		const IString s2;

};

TEST_F(NoteMapper_Tests, ValidNotes) { 
	std::vector<IString> strings = {s1, s2};
	NoteMapper map(strings);
	auto m = map.getMap();
	int noteCount = 0;
	for (auto i = m.begin(), end = m.end(); i != end; 
			i = m.upper_bound(i->first)) {
		noteCount++;
	}
	for (auto elem : m) {
		std::cout << "Note: " << elem.first << "\n";
		std::cout 
			<< "String: " 
			<< std::get<0>(elem.second) 
			<< " HP: " 
			<< std::get<1>(elem.second) 
			<< " Finger: " 
			<< std::get<2>(elem.second) << "\n";
	}
	ASSERT_EQ(noteCount, 9);
	ASSERT_EQ(m.size(), 48);
}
