#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

#include "configs.h"
#include "ConversionException.h"
#include "BasicNoteMapper.h"
#include "GreedySolver.h"
#include "Instrument.h"
#include "SolverException.h"
#include "PhysAttrMap.h"
#include "ExValException.h"
#include "SPSolver.h"

extern int TUPLESIZE;
extern std::string ATTRIBUTES_TYPES;
extern std::vector<std::string> ATTRIBUTES;

class GlobEnvironment : public ::testing::Environment {
	public:
		GlobEnvironment() {
			TUPLESIZE = 3;
			ATTRIBUTE_TYPES = "iii";
			ATTRIBUTES = {"STRING", "HAND_POS", "FINGER"};
		}
		~GlobEnvironment() override {}
		void SetUp() override {}
		void TearDown() override {}
};


//Tests a valid construction of a simplified note.
TEST(SimplifiedNote, ValidInputs) {
	using namespace mx::api;
	using namespace noteenums;

	NoteData note_ds_3 = NoteData{};

	note_ds_3.durationData.durationName = DurationName::whole;
	note_ds_3.pitchData.step = Step::d;
	note_ds_3.pitchData.octave = 3;
	note_ds_3.pitchData.alter = 1;

        const SimplifiedNote simple_note_ds_3(note_ds_3);
	const SimplifiedNote simple_note_c_4;
	const SimplifiedNote simple_note_f_3(Note::F_3, Duration::Whole);

	EXPECT_EQ(Note::Ds_3, simple_note_ds_3.getNote());
	EXPECT_EQ(Note::C_4, simple_note_c_4.getNote());
	EXPECT_EQ(Note::F_3, simple_note_f_3.getNote());
}

//Tests construction of a note higher than the allowed range of notes.
TEST(SimplifiedNote, NoteTooHigh) {
	using namespace mx::api;

	NoteData note = NoteData{};

	note.durationData.durationName = DurationName::whole;
	note.pitchData.step = Step::b;
	note.pitchData.octave = 8;
	note.pitchData.alter = 5;

	ASSERT_THROW(const SimplifiedNote simple_note(note), ConversionException);

	try {
		const SimplifiedNote simple_note(note);
	} catch (ConversionException ce) {
		EXPECT_EQ(ce.what(), "Note out of range.");
	}	
}	

//Tests construction of a note lower than the allowed range of notes.
TEST(SimplifiedNote, NoteTooLow) {
	using namespace mx::api;

	NoteData note = NoteData{};

	note.durationData.durationName = DurationName::whole;
	note.pitchData.step = Step::c;
	note.pitchData.octave = 0;
	note.pitchData.alter = -2;

	ASSERT_THROW(const SimplifiedNote simple_note(note), ConversionException);

	try {
		const SimplifiedNote simple_note(note);
	} catch (ConversionException ce) {
		EXPECT_EQ(ce.what(), "Note out of range.");
	}	
}	

//Tests construction of an undefined note.
TEST(SimplifiedNote, Undefined) {
	using namespace mx::api;

	NoteData note = NoteData{};

	ASSERT_THROW(const SimplifiedNote simple_note(note), ConversionException);
	try {
		const SimplifiedNote simple_note(note);
	} catch (ConversionException ce) {
		EXPECT_EQ(ce.what(), "Duration not found.");
	}
}

//Assert that all notes added to a string are in the same order as the vector used to 
//add them and that the notes on a string created using those notes are the same.
TEST(IString, SpecifiedNotes) {
	using namespace noteenums;

	const Note C(Note::C_3);
	const Note C_s(Note::Cs_3);
	const Note D(Note::D_3);
	const Note D_s(Note::Ds_3);
	const Note E(Note::E_3);
	const Note F(Note::F_3);
	const Note F_s(Note::Fs_3);
	const Note G(Note::G_3);
	const Note G_s(Note::Gs_3);

	const std::vector<Note> notes{C, C_s, D, D_s, E, F, F_s, G, G_s};

	const IString s(1, notes);

	for (int i = 0; i < s.getPlayable().size(); i++) {
		ASSERT_EQ(s.getPlayable()[i], notes[i]);
	}
}

//Tests that construction of IString using ranged ints results in the correct notes 
//being added in the correct order.
TEST(IString, RangedInts) {
	using namespace noteenums;

	const Note C(Note::C_3);
	const Note C_s(Note::Cs_3);
	const Note D(Note::D_3);
	const Note D_s(Note::Ds_3);
	const Note E(Note::E_3);
	const Note F(Note::F_3);
	const Note F_s(Note::Fs_3);
	const Note G(Note::G_3);
	const Note G_s(Note::Gs_3);

	const std::vector<Note> notes{C, C_s, D, D_s, E, F, F_s, G, G_s};

	const IString s(1, 36, 44);

	for (int i = 0; i < s.getPlayable().size(); i++) {
		ASSERT_EQ(s.getPlayable()[i], notes[i]);
	}
}

//Tests that the construction of IString using noteenums results in the correct notes 
//being added in the correct order.
TEST(IString, RangedNotes) {
	using namespace noteenums;

	const Note C(Note::C_3);
	const Note C_s(Note::Cs_3);
	const Note D(Note::D_3);
	const Note D_s(Note::Ds_3);
	const Note E(Note::E_3);
	const Note F(Note::F_3);
	const Note F_s(Note::Fs_3);
	const Note G(Note::G_3);
	const Note G_s(Note::Gs_3);

	const std::vector<Note> notes{C, C_s, D, D_s, E, F, F_s, G, G_s};

	const IString s(1, Note::C_3, Note::Gs_3);

	for (int i = 0; i < s.getPlayable().size(); i++) {
		ASSERT_EQ(s.getPlayable()[i], notes[i]);
	}
}

//Tests that construction of different types results in the currect type being accessable through the tuple.
TEST(ExValContainer, Types) {
	ExValContainer int_phys(1);	
	ExValContainer double_phys(1.0);	
	ExValContainer bool_phys(false);	
	ASSERT_THROW(int_phys.getB(), ExValException);
	ASSERT_THROW(int_phys.getD(), ExValException);
	ASSERT_THROW(double_phys.getB(), ExValException);
	ASSERT_THROW(double_phys.getI(), ExValException);
	ASSERT_THROW(bool_phys.getI(), ExValException);
	ASSERT_THROW(bool_phys.getD(), ExValException);

	try {
		int_phys.getB();
	} catch (ExValException e) {
		EXPECT_EQ(e.what(), "Exclusive Value is not a boolean.\n");
	}	
	try {
		int_phys.getD();
	} catch (ExValException e) {
		EXPECT_EQ(e.what(), "Exclusive Value is not a double.\n");
	}	
	try {
		double_phys.getB();
	} catch (ExValException e) {
		EXPECT_EQ(e.what(), "Exclusive Value is not a boolean.\n");
	}	
	try {
		double_phys.getI();
	} catch (ExValException e) {
		EXPECT_EQ(e.what(), "Exclusive Value is not an integer.\n");
	}	
	try {
		bool_phys.getD();
	} catch (ExValException e) {
		EXPECT_EQ(e.what(), "Exclusive Value is not a double.\n");
	}	
	try {
		bool_phys.getI();
	} catch (ExValException e) {
		EXPECT_EQ(e.what(), "Exclusive Value is not an integer.\n");
	}	
	ASSERT_EQ(int_phys.getI(), 1);
	ASSERT_EQ(double_phys.getD(), 1.0);
	ASSERT_EQ(bool_phys.getB(), false);
}

//Tests that all comparison operations on ExValContainers work as intended,
TEST(ExValContainer, ComparisonOperations) {
	ExValContainer low_int(1);
	ExValContainer high_int(8);
	ExValContainer low_double(1.0);
	ExValContainer high_double(8.0);
	ExValContainer true_bool(true);
	ExValContainer false_bool(false);

	//Equality
	ASSERT_EQ(low_int == high_int, false);
	ASSERT_EQ(low_int == low_double, false);
	ASSERT_EQ(low_int == false_bool, false);
	ASSERT_EQ(low_int == low_int, true);

	ASSERT_EQ(low_double == high_double, false);
	ASSERT_EQ(low_double == low_int, false);
	ASSERT_EQ(low_double == false_bool, false);
	ASSERT_EQ(low_double == low_double, true);

	ASSERT_EQ(false_bool == true_bool, false);
	ASSERT_EQ(false_bool == low_int, false);
	ASSERT_EQ(false_bool == low_double, false);
	ASSERT_EQ(false_bool == false_bool, true);

	//Unequality
	ASSERT_EQ(low_int != high_int, true);
	ASSERT_EQ(low_int != low_double, true);
	ASSERT_EQ(low_int != false_bool, true);
	ASSERT_EQ(low_int != low_int, false);

	ASSERT_EQ(low_double != high_double, true);
	ASSERT_EQ(low_double != low_int, true);
	ASSERT_EQ(low_double != false_bool, true);
	ASSERT_EQ(low_double != low_double, false);

	ASSERT_EQ(false_bool != true_bool, true);
	ASSERT_EQ(false_bool != low_int, true);
	ASSERT_EQ(false_bool != low_double, true);
	ASSERT_EQ(false_bool != false_bool, false);

	//Less Than
	ASSERT_EQ(low_int < high_int, true);
	ASSERT_EQ(low_int < low_double, true);
	ASSERT_EQ(low_int < false_bool, false);
	ASSERT_EQ(low_int < low_int, false);

	ASSERT_EQ(low_double < high_double, true);
	ASSERT_EQ(low_double < low_int, false);
	ASSERT_EQ(low_double < false_bool, false);
	ASSERT_EQ(low_double < low_double, false);

	ASSERT_EQ(false_bool < true_bool, true);
	ASSERT_EQ(false_bool < low_int, true);
	ASSERT_EQ(false_bool < low_double, true);
	ASSERT_EQ(false_bool < false_bool, false);

	//Greater Than
	ASSERT_EQ(low_int > high_int, false);
	ASSERT_EQ(low_int > low_double, false);
	ASSERT_EQ(low_int > false_bool, true);
	ASSERT_EQ(low_int > low_int, false);

	ASSERT_EQ(low_double > high_double, false);
	ASSERT_EQ(low_double > low_int, true);
	ASSERT_EQ(low_double > false_bool, true);
	ASSERT_EQ(low_double > low_double, false);

	ASSERT_EQ(false_bool > true_bool, false);
	ASSERT_EQ(false_bool > low_int, false);
	ASSERT_EQ(false_bool > low_double, false);
	ASSERT_EQ(false_bool > false_bool, false);
}

//Tests that all arithmetic operations on ExValContainers work as intended,
TEST(ExValContainer, ArithmeticOperations) {
	ExValContainer low_int(1);
	ExValContainer high_int(8);
	ExValContainer low_double(1.0);
	ExValContainer high_double(8.0);
	ExValContainer true_bool(true);
	ExValContainer false_bool(false);
	
	//Minus
	ASSERT_EQ(high_int - low_int, 7);
	ASSERT_EQ(high_int - high_int, 0);
	ASSERT_THROW(high_int - low_double, ExValException);
	ASSERT_THROW(high_int - false_bool, ExValException);
	
	ASSERT_EQ(high_double - low_double, 7.0);
	ASSERT_EQ(high_double - high_double, 0.0);
	ASSERT_THROW(high_double - low_int, ExValException);
	ASSERT_THROW(high_double - false_bool, ExValException);

	ASSERT_THROW(true_bool - false_bool, ExValException);
	ASSERT_THROW(true_bool - true_bool, ExValException);
	ASSERT_THROW(true_bool - low_double, ExValException);
	ASSERT_THROW(true_bool - false_bool, ExValException);
	
	//Plus
	ASSERT_EQ(high_int + low_int, 9);
	ASSERT_EQ(high_int + high_int, 16);
	ASSERT_THROW(high_int + low_double, ExValException);
	ASSERT_THROW(high_int + false_bool, ExValException);
	
	ASSERT_EQ(high_double + low_double, 9.0);
	ASSERT_EQ(high_double + high_double, 16.0);
	ASSERT_THROW(high_double + low_int, ExValException);
	ASSERT_THROW(high_double + false_bool, ExValException);

	ASSERT_THROW(true_bool + false_bool, ExValException);
	ASSERT_THROW(true_bool + true_bool, ExValException);
	ASSERT_THROW(true_bool + low_double, ExValException);
	ASSERT_THROW(true_bool + false_bool, ExValException);
	
	//Multiplication
	ASSERT_EQ(high_int * low_int, 8);
	ASSERT_EQ(high_int * high_int, 64);
	ASSERT_THROW(high_int * low_double, ExValException);
	ASSERT_THROW(high_int * false_bool, ExValException);
	
	ASSERT_EQ(high_double * low_double, 8.0);
	ASSERT_EQ(high_double * high_double, 64.0);
	ASSERT_THROW(high_double * low_int, ExValException);
	ASSERT_THROW(high_double * false_bool, ExValException);

	ASSERT_THROW(true_bool * false_bool, ExValException);
	ASSERT_THROW(true_bool * true_bool, ExValException);
	ASSERT_THROW(true_bool * low_double, ExValException);
	ASSERT_THROW(true_bool * false_bool, ExValException);
}

//Tests that all boolean operations on ExValContainers work as intended,
TEST(ExValContainer, BooleanOperations) {
	ExValContainer low_int(1);
	ExValContainer high_int(8);
	ExValContainer low_double(1.0);
	ExValContainer high_double(8.0);
	ExValContainer true_bool(true);
	ExValContainer false_bool(false);
	
	//Conjunction
	ASSERT_THROW(high_int && low_int, ExValException);
	ASSERT_THROW(high_int && high_int, ExValException);
	ASSERT_THROW(high_int && low_double, ExValException);
	ASSERT_THROW(high_int && false_bool, ExValException);
	
	ASSERT_THROW(high_double && low_double, ExValException);
	ASSERT_THROW(high_double && high_double, ExValException);
	ASSERT_THROW(high_double && low_int, ExValException);
	ASSERT_THROW(high_double && false_bool, ExValException);

	ASSERT_EQ(true_bool && false_bool, false);
	ASSERT_EQ(true_bool && true_bool, true);
	ASSERT_THROW(true_bool && low_int, ExValException);
	ASSERT_THROW(true_bool && low_double, ExValException);
	
	//Disjunction
	ASSERT_THROW(high_int || low_int, ExValException);
	ASSERT_THROW(high_int || high_int, ExValException);
	ASSERT_THROW(high_int || low_double, ExValException);
	ASSERT_THROW(high_int || false_bool, ExValException);
	
	ASSERT_THROW(high_double || low_double, ExValException);
	ASSERT_THROW(high_double || high_double, ExValException);
	ASSERT_THROW(high_double || low_int, ExValException);
	ASSERT_THROW(high_double || false_bool, ExValException);

	ASSERT_EQ(true_bool || false_bool, true);
	ASSERT_EQ(true_bool || true_bool, true);
	ASSERT_THROW(true_bool || low_int, ExValException);
	ASSERT_THROW(true_bool || low_double, ExValException);
}

//Tests that init of PhysAttrMap using a pair list will result in a thrown exception if there are too many 
//attributes specified.
TEST(PhysAttrMap, PairListTooManyAttributes) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	ASSERT_THROW(const PhysAttrMap failed_map_pair({{"STRING", 5}, {"HAND_POS", 5}, {"STRING", 5}, {"FINGER", 5}}), ExValException);
	try {
		const PhysAttrMap failed_map_pair({{"STRING", 5}, {"HAND_POS", 5}, {"STRING", 5}, {"FINGER", 5}});
	} catch (ExValException e) {
		ASSERT_EQ(e.what(), "List size is not the same as TUPLESIZE.");
	}
}

//Tests that init of PhysAttrMap using a pair list will result in a thrown exception if the types of the 
//fundamentals do not match the ATTRIBUTE_TYPES.
TEST(PhysAttrMap, PairListWrongAttributeTypes) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	ASSERT_THROW(const PhysAttrMap failed_map_pair({{"STRING", 5}, {"HAND_POS", 5.0}, {"FINGER", 5}}), ExValException);
	try {
		const PhysAttrMap failed_map_pair({{"STRING", 5}, {"HAND_POS", 5.0}, {"FINGER", 5}});
	} catch (ExValException e) {
		ASSERT_EQ(e.what(), "Attribute map is not consistent with attribute types.");
	}
}

//Tests that init of PhysAttrMap using a pair list will result in a thrown exception if the types of the
//fundamentals match the ATTRIBUTE_TYPES but not in the order they are defined in ATTRIBUTES.
TEST(PhysAttrMap, PairList) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	ATTRIBUTE_TYPES = "iid";
	ASSERT_THROW(const PhysAttrMap failed_map_pair({{"STRING", 5}, {"FINGER", 5}, {"HAND_POS", 5.0}}), ExValException);
	
	try {
		const PhysAttrMap failed_map_pair({{"STRING", 5}, {"FINGER", 5}, {"HAND_POS", 5.0}});
	} catch (ExValException e) {
		ASSERT_EQ(e.what(), "Attribute map is not consistent with attribute types.");
	}
}

//Tests that init of PhysAttrMap using a pair list will throw an exception if two of the attributes are of
//the same type.
TEST(PhysAttrMap, PairListDupeAttribute) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	ASSERT_THROW(const PhysAttrMap failed_map_pair({{"STRING", 5}, {"STRING", 2}, {"FINGER", 5}}), ExValException);
	
	try {
		const PhysAttrMap failed_map_pair({{"STRING", 5}, {"STRING", 5}, {"FINGER", 5}});
	} catch (ExValException e) {
		ASSERT_EQ(e.what(), "Attribute map already contains a value of this attribute type.");
	}
}

//Tests that getting values from a pair-list PhysAttrMap init results in the correct values and exception
//when trying to get a non-existant value.
TEST(PhysAttrMap, PairListGetVals) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	PhysAttrMap map_pair({{"STRING", 2}, {"FINGER", 1}, {"HAND_POS", 4}});

	ASSERT_EQ(map_pair.getVal("STRING"), 2);
	ASSERT_EQ(map_pair.getVal("FINGER"), 1);
	ASSERT_EQ(map_pair.getVal("HAND_POS"), 4);
	ASSERT_THROW(map_pair.getVal("NON_EXISTANT"), std::out_of_range);
}

//Tests that init of PhysAttrMap using a list init will result in a thrown exception if the list contains 
//more arguments than the tuplesize
TEST(PhysAttrMap, ImplicitListTooManyAttributes) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	ASSERT_THROW(const PhysAttrMap failed_map_implicit({2, 5, 7, 2}), ExValException);
	try {
		const PhysAttrMap failed_map_implicit({2, 5, 7, 2});
	} catch (ExValException e) {
		ASSERT_EQ(e.what(), "List size is not the same as TUPLESIZE.");
	}
}

//Tests that init of PhysAttrMap using a list init will fail if one of the arguements does not line up with
//the specified ATTRIBUTE_TYPES
TEST(PhysAttrMap, ImplicitListWrongAttributeTypes) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	ASSERT_THROW(const PhysAttrMap failed_map_implicit({2, 5, 2.2}), ExValException);
	try {
		const PhysAttrMap failed_map_implicit({2, 5, 2.2});
	} catch (ExValException e) {
		ASSERT_EQ(e.what(), "Attribute map is not consistent with attribute types.");
	}
}

//Tests that getting values from a implicit-list PhysAttrMap init results in the correct values and 
//exception when trying to get a non-existant value.
TEST(PhysAttrMap, ImplicitListGetVals) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	PhysAttrMap map_implicit({2, 1, 4});

	ASSERT_EQ(map_implicit.getVal("STRING"), 2);
	ASSERT_EQ(map_implicit.getVal("HAND_POS"), 1);
	ASSERT_EQ(map_implicit.getVal("FINGER"), 4);
	ASSERT_THROW(map_implicit.getVal("NON_EXISTANT"), std::out_of_range);
}

//Tests that boolean operations result in the expected results regardless of initialization method used.
TEST(PhysAttrMap, BooleanOperations) {
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	PhysAttrMap implicit_one{2, 5, 3};
	PhysAttrMap implicit_two{4, 5, 1};
	PhysAttrMap pair_one({{"STRING", 2}, {"FINGER", 3}, {"HAND_POS", 5}});
	PhysAttrMap pair_two({{"FINGER", 1}, {"STRING", 4}, {"HAND_POS", 5}});

	//Equality
	ASSERT_EQ(implicit_one == implicit_one, true);
	ASSERT_EQ(implicit_one == implicit_two, false);
	ASSERT_EQ(implicit_one == pair_one, true);
	ASSERT_EQ(implicit_one == pair_two, false);
	
	//Unequality
	ASSERT_EQ(implicit_one != implicit_one, false);
	ASSERT_EQ(implicit_one != implicit_two, true);
	ASSERT_EQ(implicit_one != pair_one, false);
	ASSERT_EQ(implicit_one != pair_two, true);
}

//Tests that an empty NoteList is the result of an empty score.
TEST(NoteList, Undefined) {
	using namespace mx::api;

	ScoreData score = ScoreData{};

	const NoteList note_list(score);

	ASSERT_EQ(note_list.size(), 0);
}

//Test to make sure notes preserve their order when placed into a notelist from a 
//score.
TEST(NoteList, OrderPreserved) {
	using namespace noteenums;
	using namespace mx::api;

	//Build structs
	ScoreData score = ScoreData{};
	score.parts.emplace_back(PartData{});
	PartData& part = score.parts.back();
	part.measures.emplace_back(MeasureData{});
	MeasureData& measure = part.measures.back();
	measure.staves.emplace_back(StaffData{});
	StaffData& staff = measure.staves.back();
	staff.voices[0] = VoiceData{};
	VoiceData& voice = staff.voices.at(0);
	auto currentTime = 0;
	
	//Add notes
	NoteData note = NoteData{};
	note.pitchData.step = Step::a;
	note.pitchData.alter = 0;
	note.pitchData.octave = 4;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::b;
	note.pitchData.alter = 0;
	note.pitchData.octave = 4;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::c;
	note.pitchData.alter = 0;
	note.pitchData.octave = 5;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::d;
	note.pitchData.alter = 0;
	note.pitchData.octave = 5;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::e;
	note.pitchData.alter = 0;
	note.pitchData.octave = 5;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;

	const NoteList notes(score);

	auto note_itr = notes.getNotes().begin();
	
	ASSERT_EQ(notes.size(), 5);

	ASSERT_EQ(note_itr++->getNote(), Note::A_4);

	ASSERT_EQ(note_itr++->getNote(), Note::B_4);
	
	ASSERT_EQ(note_itr++->getNote(), Note::C_5);
	
	ASSERT_EQ(note_itr++->getNote(), Note::D_5);
	
	ASSERT_EQ(note_itr->getNote(), Note::E_5);
}

class BasicNoteMapper_Tests : public ::testing::Test {
	public:
	       	BasicNoteMapper_Tests() : s1(1, noteenums::Note::C_3, noteenums::Note::A_3), 
					  s2(2, noteenums::Note::Ds_3, noteenums::Note::C_4) {}
		const IString s1;
		const IString s2;
};

//Tests that the basic notemapper returns the correct amount of notes and amount of 
//combinations.
TEST_F(BasicNoteMapper_Tests, ValidNotes) {
        using namespace noteenums;
	using namespace std;
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	unique_ptr<NoteMapper>map(new BasicNoteMapper({s1, s2}));
	
	int note_count = 0;
	for (auto i = map->getMap().begin(), end = map->getMap().end(); i != end;
		  i = map->getMap().upper_bound(i->first)) {
		note_count++;
	}

	for (auto& elem : map->getMap()) {
		cout << "Note: " << elem.first << "\n";
		cout << "String: " << elem.second.getVal("STRING")
			<< " HP: " << elem.second.getVal("HAND_POS")
			<< " Finger: " << elem.second.getVal("FINGER") << "\n";
	}
	ASSERT_EQ(note_count, 14);
	ASSERT_EQ(map->size(), 33);
}

//Tests that all combinations constructed for 4 notes in the notemapper are the 
//valid combinations for those notes.
TEST_F(BasicNoteMapper_Tests, SampleTests) {
	using namespace noteenums;
	using namespace mx::api;
	using namespace std;
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);

	unique_ptr<NoteMapper>map(new BasicNoteMapper({s1, s2}));

	auto C3 = map->getMap().equal_range(Note::C_3);
	auto D_3 = map->getMap().equal_range(Note::D_3);
	auto E3 = map->getMap().equal_range(Note::E_3);
	auto As_3 = map->getMap().equal_range(Note::As_3);

	int comb_count = 0;
	//Check valid combinations for C_3.
	for (auto i = C3.first; i != C3.second; i++) {
		comb_count++;
		if (comb_count == 1) {
			ASSERT_EQ(i->second.getVal("STRING"), 1);
			ASSERT_EQ(i->second.getVal("HAND_POS"), 0);
			ASSERT_EQ(i->second.getVal("FINGER"), 0);
		}
	}
	//Check valid combinations for D_3.
	for (auto i = D_3.first; i != D_3.second; i++) {
		comb_count++;
		if (comb_count == 2) {
			ASSERT_EQ(i->second.getVal("STRING"), 1);
			ASSERT_EQ(i->second.getVal("HAND_POS"), 1);
			ASSERT_EQ(i->second.getVal("FINGER"), 1);
		}
	}
	//Check valid combinations for E_3.
	for (auto i = E3.first; i != E3.second; i++) {
		comb_count++;
		if (comb_count == 3) {
			ASSERT_EQ(i->second.getVal("STRING"), 1);
			ASSERT_EQ(i->second.getVal("HAND_POS"), 1);
			ASSERT_EQ(i->second.getVal("FINGER"), 2);
		} else if (comb_count == 4) {
			ASSERT_EQ(i->second.getVal("STRING"), 1);
			ASSERT_EQ(i->second.getVal("HAND_POS"), 2);
			ASSERT_EQ(i->second.getVal("FINGER"), 1);
		} else if (comb_count == 5) {
			ASSERT_EQ(i->second.getVal("STRING"), 2);
			ASSERT_EQ(i->second.getVal("HAND_POS"), 1);
			ASSERT_EQ(i->second.getVal("FINGER"), 1);
		}
	}
	//Check valid combinations for As_3.
	for (auto i = As_3.first; i != As_3.second; i++) {
		comb_count++;
		if (comb_count == 6) {
			ASSERT_EQ(i->second.getVal("STRING"), 2);
			ASSERT_EQ(i->second.getVal("HAND_POS"), 1);
			ASSERT_EQ(i->second.getVal("FINGER"), 4);
		} else if (comb_count == 7) {
			ASSERT_EQ(i->second.getVal("STRING"), 2);
			ASSERT_EQ(i->second.getVal("HAND_POS"), 2);
			ASSERT_EQ(i->second.getVal("FINGER"), 3);
		} 
	}
	//Ensure there are no more unchecked combinations.
	ASSERT_EQ(comb_count, 7);
}

//Tests that only allowed strings, hand positions, and finger numbers are used.
TEST_F(BasicNoteMapper_Tests, ValidPosition) {
	using namespace noteenums;
	using namespace mx::api;
	using namespace testing;
	using namespace std;
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);

	unique_ptr<NoteMapper> map(new BasicNoteMapper({s1, s2}));

	for (auto i = map->getMap().begin(); i != map->getMap().end(); i++) {
		if (i->first != Note::REST) {
			ASSERT_THAT(i->second.getVal("STRING"), AllOf(Lt(3), Gt(0)));
			ASSERT_THAT(i->second.getVal("HAND_POS"), AllOf(Lt(3), Gt(-1)));
			ASSERT_THAT(i->second.getVal("FINGER"), AllOf(Lt(5), Gt(-1)));
		} else {
			ASSERT_THAT(i->second.getVal("FINGER"), AllOf(Lt(1), Gt(-1)));
		}
	}
}
//Tests that a basic action using a 3-tuple with an int return returns the proper
//distance and condition.
TEST(Action, BasicAction) {
	using namespace std;
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);

	typedef bool (*a_type_cond)(PhysAttrMap, PhysAttrMap);
	typedef int (*a_type_dist)(PhysAttrMap, PhysAttrMap);

	a_type_cond d_f_cond = [] (PhysAttrMap t1, PhysAttrMap t2) {
		return true;
	};
	a_type_dist d_f_dist = [] (PhysAttrMap t1, PhysAttrMap t2) {
		int string = abs((int)(t1.getVal("STRING") - t2.getVal("STRING")));
		int hand = abs((int)(t1.getVal("HAND_POS") - t2.getVal("HAND_POS")));
		int finger = abs((int)(t1.getVal("FINGER") - t2.getVal("FINGER")));
		return string + hand + finger;	
	};
	const Action<int> NOC(d_f_cond, d_f_dist, "NOC");

	const PhysAttrMap t1({{"STRING", 1}, 
			      {"HAND_POS", 1}, 
			      {"FINGER", 1}});
	const PhysAttrMap t2({{"STRING", 2}, 
			      {"HAND_POS", 2}, 
			      {"FINGER", 2}});

	ASSERT_EQ(NOC.distance(t1, t2), 3);
	ASSERT_EQ(NOC.condition(t1, t2), true);
}

//Tests that a more complex action using floats and booleans returns the correct
//distance and condition.
TEST(Action, FiveTupleAction) {
	using namespace std;
	TUPLESIZE = 5;
	ATTRIBUTE_TYPES = "iiibd";
	ATTRIBUTES = {"STRING", "HAND_POS", "FINGER", "UP_STROKE", "B_DISTANCE"};

	typedef bool (*a_type_cond)(PhysAttrMap, PhysAttrMap);
	typedef double (*a_type_dist)(PhysAttrMap, PhysAttrMap);

	a_type_dist d_f_dist = [] (PhysAttrMap s1, PhysAttrMap s2) {
		int string = abs(int(s1.getVal("STRING") - s2.getVal("STRING")));
		int hand = abs(int(s1.getVal("HAND_POS") - s2.getVal("HAND_POS")));
		int finger = abs(int(s1.getVal("FINGER") - s2.getVal("FINGER")));
		bool up_stroke = s1.getVal("UP_STROKE") || s2.getVal("UP_STROKE");
		double note_distance = abs(double(s1.getVal("B_DISTANCE") - s2.getVal("B_DISTANCE")));
		double res;

	       	if (up_stroke) {
			res = (string + hand + finger) * note_distance;
		} else{
			res = (string + hand + finger);
		}
		return static_cast<double>(res);
	};
	a_type_cond d_f_cond = [] (PhysAttrMap s1, PhysAttrMap s2) {
		return true;
	};
	const Action<double> upstroke_distance(d_f_cond, d_f_dist, "UD");

	const PhysAttrMap t1({1, 2, 1, false, 3.0});
	const PhysAttrMap t2({1, 2, 3, false, 7.0});
	const PhysAttrMap t3({1, 2, 1, true, 3.0});
	const PhysAttrMap t4({1, 2, 3, false, 7.0});

	ASSERT_EQ(upstroke_distance.distance(t1, t2), 2.0);
	ASSERT_EQ(upstroke_distance.distance(t3, t4), 8.0);
}

class Layer_Tests : public ::testing::Test {
	typedef std::tuple<int, int, int> ret;
	public:
		Layer_Tests() : l(noteenums::Note::C_3, noteenums::Duration::Whole) {
			::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
		}
		void SetUp() override {
			l.clear();
		}
		void TearDown() override {
			l.clear();
		}
		Layer l;
};

//Tests that creating a basic layer using add and remove results in the correct
//tuples are being added and removed.
TEST_F(Layer_Tests, BasicLayer) {
	using namespace mx::api;
	
	const PhysAttrMap first{1, 1, 1};

	EXPECT_NO_THROW(l.addNode(first));
	ASSERT_EQ(l.getSize(), 1);

	const PhysAttrMap second{2, 1, 1};

	EXPECT_NO_THROW(l.addNode(second));
	ASSERT_EQ(l.getSize(), 2);
	EXPECT_NO_THROW(l.removeNode(first));
	ASSERT_EQ(l.getSize(), 1);

	const PhysAttrMap third{1, 2, 1};

	EXPECT_NO_THROW(l.addNode(third));
	ASSERT_EQ(l.getSize(), 2);

	const PhysAttrMap fourth{1, 1, 2};

	EXPECT_NO_THROW(l.addNode(fourth));
	ASSERT_EQ(l.getSize(), 3);
	EXPECT_NO_THROW(l.removeNode(fourth));
	ASSERT_EQ(l.getSize(), 2);
}

//Tests that adding a duplicate node results in -1 and fails to add the second 
//node while retaining first node.
TEST_F(Layer_Tests, AddSameNodeTwice) {
	using namespace mx::api;

	const PhysAttrMap first{1, 1, 1};
	const PhysAttrMap second{1, 1, 1};

	EXPECT_EQ(l.addNode(first), 1);
	ASSERT_EQ(l.addNode(second), -1);
	ASSERT_EQ(l.getSize(), 1);
	ASSERT_EQ(l[0], first);
}

//Tests that failure to remove a non-existant node returns -1 and retains first node.
TEST_F(Layer_Tests, RemoveNonexistantNode) {
	using namespace mx::api;
	
	const PhysAttrMap first{1, 1, 1};	
	const PhysAttrMap second{2, 2, 2};

	EXPECT_EQ(l.addNode(first), 1);
	ASSERT_EQ(l.removeNode(second), -1);
	ASSERT_EQ(l.getSize(), 1);
	ASSERT_EQ(l[0], first);
}

class ActionSet_Tests : public ::testing::Test {
	using out_type = int;

	typedef out_type (*a_type_dist)(PhysAttrMap, PhysAttrMap);
	typedef bool (*a_type_cond)(PhysAttrMap, PhysAttrMap);

	public:
		std::unique_ptr<ActionSet<out_type>> set;
		ActionSet_Tests() {		
			::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
			using namespace std;

			a_type_cond fa_cond = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return true;
			};
			a_type_dist fa_dist = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return int(max(s1.getVal("FINGER"), s2.getVal("FINGER"))
				       - min(s1.getVal("FINGER"), s2.getVal("FINGER")));
			};
			const Action<out_type> f_a(fa_cond, fa_dist, "FA");
			
			a_type_cond ha_cond = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return true;
			};
			a_type_dist ha_dist = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return int(max(s1.getVal("HAND_POS"), s2.getVal("HAND_POS"))
					 - min(s1.getVal("HAND_POS"), s2.getVal("HAND_POS")));
			};
			const Action<out_type> h_a(ha_cond, ha_dist, "HA");
			
			a_type_cond sa_cond = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return true;
			};
			a_type_dist sa_dist = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return int(max(s1.getVal("STRING"), s2.getVal("STRING"))
					- min(s1.getVal("STRING"), s2.getVal("STRING")));
			};
			const Action<out_type> s_a(sa_cond, sa_dist, "SA");

			set = unique_ptr<ActionSet<out_type>>(new ActionSet<out_type>{
							{f_a, true}, 
							{h_a, true}, 
							{s_a, true}
							});
		}
};

//Tests that the distance between different inputs corresponds with the actions in 
//the ActionSet
TEST_F(ActionSet_Tests, CorrectDistance) {
	const PhysAttrMap f1 = {0, 0, 0};
	const PhysAttrMap s1 = {1, 2, 1};

	ASSERT_EQ(set->apply(f1, s1), 4);

	const PhysAttrMap f2 = {2, 2, 2};
	const PhysAttrMap s2 = {0, 3, 2};

	ASSERT_EQ(set->apply(f2, s2), 3);
}

//Tests that dependencies correctly disable actions and cannot re-enable them.
TEST_F(ActionSet_Tests, Dependencies) {
	set->addDependency("HA", "FA", false);

	const PhysAttrMap f1 = {0, 0, 0};
	const PhysAttrMap s1 = {1, 10, 1};

	ASSERT_EQ(set->apply(f1, s1), 2);	

	set->addDependency("SA", "FA", false);

	ASSERT_EQ(set->apply(f1, s1), 1);	

	set->addDependency("SA", "FA", true);

	ASSERT_EQ(set->apply(f1, s1), 1);	
}

class LayerList_Tests : public ::testing::Test {
	using out_type = int;

	public:
		std::unique_ptr<LayerList<int>> list;
		LayerList_Tests() {
			using namespace noteenums;
			using namespace std;
			::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);

			typedef out_type (*a_type_dist) (PhysAttrMap, PhysAttrMap);
			typedef bool (*a_type_cond) (PhysAttrMap, PhysAttrMap);

			const IString s1(1, Note::C_3, Note::B_3);
			const IString s2(2, Note::G_3, Note::Ds_4);

			std::shared_ptr<NoteMapper> note_mapper(new BasicNoteMapper({s1, s2}));

			const Layer first(Note::D_3, Duration::Whole, note_mapper);
			const Layer second(Note::Fs_3, Duration::Whole, note_mapper);
			const Layer third(Note::G_3, Duration::Whole, note_mapper);
			const Layer fourth(Note::Cs_4, Duration::Whole, note_mapper);

			vector<Layer> l_vec({first, second, third, fourth});

			list = unique_ptr<LayerList<int>>(new LayerList<out_type>(l_vec));

			a_type_cond fa_cond = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return true;
			};
			a_type_dist fa_dist = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return int(max(s1.getVal("FINGER"), s2.getVal("FINGER")) - min(s1.getVal("FINGER"), s2.getVal("FINGER")));
			};
			const Action<out_type> f_a(fa_cond, fa_dist, "FA");
			
			a_type_cond ha_cond = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return true;
			};
			a_type_dist ha_dist = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return int(max(s1.getVal("HAND_POS"), s2.getVal("HAND_POS")) - min(s1.getVal("HAND_POS"), s2.getVal("HAND_POS")));
			};
			const Action<out_type> h_a(ha_cond, ha_dist, "HA");
			
			a_type_cond sa_cond = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return true;
			};
			a_type_dist sa_dist = [] (PhysAttrMap s1, PhysAttrMap s2) {
				return int(max(s1.getVal("STRING"), s2.getVal("STRING")) - min(s1.getVal("STRING"), s2.getVal("STRING")));
			};
			const Action<out_type> s_a(sa_cond, sa_dist, "SA");
			
			std::shared_ptr<ActionSet<out_type>> actions(new ActionSet<out_type>());
			actions->makeAction(fa_cond, fa_dist, "FA", true);
			actions->makeAction(ha_cond, ha_dist, "HA", true);
			actions->makeAction(sa_cond, sa_dist, "SA", true);
			
			list->buildTransitions(actions);
		}
};

//Tests that the list contains all constructed layers and the layers have the 
//correct amount of nodes.
TEST_F(LayerList_Tests, CountAndLayerCount) {
	int count = 0;
	for (auto& l : *list) {
		count++;
	}

	ASSERT_EQ(count, 4);

	auto l_it = list->begin();

	ASSERT_EQ(l_it++->getElem().getSize(), 1);
	ASSERT_EQ(l_it++->getElem().getSize(), 3);
	ASSERT_EQ(l_it++->getElem().getSize(), 4);
	ASSERT_EQ(l_it++->getElem().getSize(), 1);
}

//Tests that the transitions between layers are calculated correctly.
TEST_F(LayerList_Tests, Transitions) {
	using namespace std;

	auto l_it = list->begin();

	//Outputs 
	const vector<int> outputs = {2, 2, 2, 
			       	     1, 1, 3, 5, 3, 1, 1, 5, 5, 3, 1, 5,
			       	     2, 2, 4, 4
			       	     };
	int count = 0;
	//D_3 = {1, 1, 1}
	for (int i = 0; i < l_it->getTransitions().size(); i++) {
		cout << l_it->getElem()[i] << "\n";
		for (auto& output : l_it->getTransitions()[i]) {
			cout << "Count: " 
			     << count 
			     << "\nOutput D -> Fs: " 
			     << output 
			     << "\n";

			ASSERT_EQ(output, outputs[count]);
			count++;
		}
	}

	l_it++;
	//Fs_3 = {1, 1, 3}, {1, 2, 2}, {1, 3, 1}
	for (int i = 0; i < l_it->getTransitions().size(); i++) {
		cout << l_it->getElem()[i] << "\n";
		for (auto& output : l_it->getTransitions()[i]) {
			cout << "Count: " 
			     << count 
			     << "\nOutput Fs -> G: " 
			     << output 
			     << "\n";

			ASSERT_EQ(output, outputs[count]);
			count++;
		}
	}

	l_it++;
	//G_3 = {1, 1, 4}, {1, 2, 3}, {1, 3, 2}, {2, 0, 0}
	for (int i = 0; i < l_it->getTransitions().size(); i++) {
		cout << l_it->getElem()[i] << "\n";
		for (auto& output : l_it->getTransitions()[i]) {
			cout << "Count: " 
			     << count 
			     << "\nOutput G -> Cs: " 
			     << output 
			     << "\n";

			ASSERT_EQ(output, outputs[count]);
			count++;
		}
	}

	//Cs_4 = {2, 1, 3} -- Does not transition out
	l_it++;
	for (int i = 0; i < l_it->getTransitions().size(); i++) {
		for (auto& output : l_it->getTransitions()[i]) {
			ASSERT_EQ(output, -1);
			count++;
		}
	}
}

//Non-fixture layerlist test to verify data coming directly from a notelist can be
//processed properly into a layerlist and results in the correct layers being added.
TEST(LayerList, FromNoteList) {
	using namespace noteenums;
	using namespace mx::api;

	//Build structs
	ScoreData score = ScoreData{};
	score.parts.emplace_back(PartData{});
	PartData& part = score.parts.back();
	part.measures.emplace_back(MeasureData{});
	MeasureData& measure = part.measures.back();
	measure.staves.emplace_back(StaffData{});
	StaffData& staff = measure.staves.back();
	staff.voices[0] = VoiceData{};
	VoiceData& voice = staff.voices.at(0);
	auto currentTime = 0;
	
	//Add notes
	NoteData note = NoteData{};
	note.pitchData.step = Step::a;
	note.pitchData.alter = 0;
	note.pitchData.octave = 4;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::b;
	note.pitchData.alter = 0;
	note.pitchData.octave = 4;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::c;
	note.pitchData.alter = 0;
	note.pitchData.octave = 5;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::d;
	note.pitchData.alter = 0;
	note.pitchData.octave = 5;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;
	
	note.pitchData.step = Step::e;
	note.pitchData.alter = 0;
	note.pitchData.octave = 5;
	note.durationData.durationName = DurationName::whole;
	note.tickTimePosition = currentTime;
	voice.notes.push_back(note);
	currentTime += 1;

	const NoteList notes(score);

	std::shared_ptr<NoteMapper>note_mapper(new BasicNoteMapper());
	
	LayerList<int> l1(notes, note_mapper);
	
	int count = 0;
	for (auto& l : l1) {
		count++;
	}

	ASSERT_EQ(count, 5);

	auto it = l1.begin();

	ASSERT_EQ(it++->getElem().getNote().getNote(), Note::A_4);
	ASSERT_EQ(it++->getElem().getNote().getNote(), Note::B_4);
	ASSERT_EQ(it++->getElem().getNote().getNote(), Note::C_5);
	ASSERT_EQ(it++->getElem().getNote().getNote(), Note::D_5);
	ASSERT_EQ(it++->getElem().getNote().getNote(), Note::E_5);
}

//Tests that strings created in an instrument exist in the correct order and contain the correct notes.
TEST(Instrument_Test, CorrectStrings) {
	using out_type = int;
	
	using namespace noteenums;

	std::shared_ptr<ActionSet<out_type>> dummy(new ActionSet<out_type>());

	Instrument<out_type> inst(dummy);

	inst.makeIString(1, Note::E_4, Note::E_6);
	inst.makeIString(2, Note::Ds_2, Note::F_3);
	
	std::vector<Note> notes_1{
		Note::E_4, Note::F_4, Note::Fs_4, Note::G_4, Note::Gs_4, Note::A_4, Note::As_4, Note::B_4,
		Note::C_5, Note::Cs_5, Note::D_5, Note::Ds_5, Note::E_5, Note::F_5, Note::Fs_5, Note::G_5,
		Note::Gs_5, Note::A_5, Note::As_5, Note::B_5, Note::C_6, Note::Cs_6, Note::D_6, Note::Ds_6,
		Note::E_6};

	std::vector<Note> notes_2{
		Note::Ds_2, Note::E_2, Note::F_2, Note::Fs_2, Note::G_2, Note::Gs_2, Note::A_2, 
		Note::As_2, Note::B_2, Note::C_3, Note::Cs_3, Note::D_3, Note::Ds_3, Note::E_3, Note::F_3};

	int count = 1;
	for (const IString& s : inst.getIStrings()) {
		int index = 0;
		for (auto n : s.getPlayable()) {
			if (count == 1) {
				ASSERT_EQ(n, notes_1[index++]);
			} else if (count == 2) {
				ASSERT_EQ(n, notes_2[index++]);
			}
		}
		count++;
	}
}

//Tests that trying to insert a string with an invalid position. 
TEST(Instrument_Test, IncorrectPos) {
	using namespace noteenums;
	using out_type = int;

	std::shared_ptr<ActionSet<out_type>> dummy(new ActionSet<out_type>());
	
	Instrument<out_type> inst(dummy);

	inst.makeIString(-1, Note::E_4, Note::E_6);

	ASSERT_EQ(inst.getIStrings().size(), 0);
}

//Tests that adding two strings with the same position results in the first being kept and the second 
//discarded.
TEST(Instrument_Test, DupePosition) {
	using namespace noteenums;
	using out_type = int;

	std::shared_ptr<ActionSet<out_type>> dummy(new ActionSet<out_type>());
	
	Instrument<out_type> inst(dummy);

	inst.makeIString(1, Note::E_4, Note::E_6);
	inst.makeIString(1, Note::Ds_2, Note::F_3);
	
	std::vector<Note> notes_1{
		Note::E_4, Note::F_4, Note::Fs_4, Note::G_4, Note::Gs_4, Note::A_4, Note::As_4, Note::B_4,
		Note::C_5, Note::Cs_5, Note::D_5, Note::Ds_5, Note::E_5, Note::F_5, Note::Fs_5, Note::G_5,
		Note::Gs_5, Note::A_5, Note::As_5, Note::B_5, Note::C_6, Note::Cs_6, Note::D_6, Note::Ds_6,
		Note::E_6};

	std::vector<Note> notes_2{
		Note::Ds_2, Note::E_2, Note::F_2, Note::Fs_2, Note::G_2, Note::Gs_2, Note::A_2, 
		Note::As_2, Note::B_2, Note::C_3, Note::Cs_3, Note::D_3, Note::Ds_3, Note::E_3, Note::F_3};

	int count = 1;
	for (const IString& s : inst.getIStrings()) {
		int index = 0;
		for (auto n : s.getPlayable()) {
			if (count == 1) {
				ASSERT_EQ(n, notes_1[index++]);
			} else if (count == 2) {
				FAIL();
			}
		}
		count++;
	}
}

class GreedySolver_Tests : public ::testing::Test {
	using out_type = int;

	private:
		Instrument<out_type> buildInstrument() {
			using namespace std;

			typedef out_type (*action_type_dist)(PhysAttrMap, PhysAttrMap);
			typedef bool (*action_type_cond)(PhysAttrMap, PhysAttrMap);
			

			action_type_cond action_cond = [] (PhysAttrMap t1, PhysAttrMap t2) {
				return true;
			};
			action_type_dist action_dist = [] (PhysAttrMap t1, PhysAttrMap t2) {
				int out = abs(int(t1.getVal("HAND_POS") - t2.getVal("HAND_POS")));
				out = out + abs(int(t1.getVal("FINGER") - t2.getVal("FINGER")));
				if (abs(int(t1.getVal("STRING") - t2.getVal("STRING"))) >= 2) {
					out = out + 100;
				} else {
					out = out + 1; //TODO always adds 1, even if string same
				}
				return out;
			};
			const Action<out_type> a1(action_cond, action_dist, "A1");
			
			std::shared_ptr<ActionSet<out_type>> set(new ActionSet<out_type>({a1, true}));

			Instrument<out_type> i(set);
			i.makeIString(1, Note::C_3, Note::G_3);
			i.makeIString(2, Note::D_3, Note::A_3);
			i.makeIString(3, Note::E_3, Note::B_3);
			return i;
		}
	public:
		GreedySolver_Tests() : instrument(buildInstrument()) {
			::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
		}
		Instrument<out_type> instrument;
};

//Tests that the greedysolver selects the correct path and outputs the correct costs.
TEST_F(GreedySolver_Tests, Basic) {
	using namespace noteenums;
	using namespace std;

	using out_type = int;	
		
	std::shared_ptr<NoteMapper> note_mapper(new BasicNoteMapper(instrument.getIStrings()));
	
	std::unique_ptr<GraphSolver<out_type>> solver(new GreedySolver());
	
	const Layer first(Note::C_3, Duration::Whole, note_mapper);
	const Layer second(Note::E_3, Duration::Whole, note_mapper);
	const Layer third(Note::Gs_3, Duration::Whole, note_mapper);

	LayerList<out_type> l_list({first, second, third});
	l_list.buildTransitions(instrument.getActionSet());			

	solver->solve(l_list);

	//C_3 = {1, 0, 0}
	//E_3 = {1, 1, 2}, {2, 1, 1}, {3, 0, 0}
	//Gs_3 = {3, 1, 3}, {3, 1, 2}

	const PhysAttrMap sol_1({1, 0, 0});
	const PhysAttrMap sol_2({2, 1, 1});
	const PhysAttrMap sol_3({3, 1, 2});

	const int cost_1 = 3;
	const int cost_2 = 2;
	const int cost_3 = -1;

	int count = 0;
	for (auto sol : solver->getSolution()) {
		if (count == 0) {
			ASSERT_EQ(get<0>(sol).getState(), sol_1);
			ASSERT_EQ(get<1>(sol), cost_1);
		} else if (count == 1) {
			ASSERT_EQ(get<0>(sol).getState(), sol_2);
			ASSERT_EQ(get<1>(sol), cost_2);
		} else if (count == 2) {
			ASSERT_EQ(get<0>(sol).getState(), sol_3);
			ASSERT_EQ(get<1>(sol), cost_3);
		}
		count++;
	}
}

TEST(SPSolver_Tests, Basic) {
	using namespace noteenums;
	using namespace std;
	::testing::Environment* const env = ::testing::AddGlobalTestEnvironment(new GlobEnvironment);
	using out_type = int;

	typedef out_type (*action_type_dist)(PhysAttrMap, PhysAttrMap);
	typedef bool (*action_type_cond)(PhysAttrMap, PhysAttrMap);
	

	action_type_cond action_cond = [] (PhysAttrMap t1, PhysAttrMap t2) {
		return true;
	};
	action_type_dist action_dist = [] (PhysAttrMap t1, PhysAttrMap t2) {
		int out = abs(int(t1.getVal("HAND_POS") - t2.getVal("HAND_POS")));
		out = out + abs(int(t1.getVal("FINGER") - t2.getVal("FINGER")));
		if (abs(int(t1.getVal("STRING") - t2.getVal("STRING"))) >= 2) {
			out = out + 100;
		} else {
			out = out + 1;
		}
		return out;
	};
	const Action<out_type> a1(action_cond, action_dist, "A1");
	
	std::shared_ptr<ActionSet<out_type>> set(new ActionSet<out_type>({a1, true}));

	Instrument<out_type> i(set);
	i.makeIString(1, Note::C_3, Note::G_3);
	i.makeIString(2, Note::D_3, Note::A_3);
	i.makeIString(3, Note::E_3, Note::B_3);

	using out_type = int;	
		
	std::shared_ptr<NoteMapper> note_mapper(new BasicNoteMapper(i.getIStrings()));
	
	std::unique_ptr<GraphSolver<out_type>> solver(new SPSolver<int>(0));
	
	//C_3 = {1, 0, 0}
	//E_3 = {1, 1, 2}, {2, 1, 1}, {3, 0, 0}
	//Gs_3 = {2, 1, 3}, {3, 1, 2}
	//G_3 = {1, 1, 4}, {2, 1, 3}, {3, 1, 2}
	//A_3 = {2, 1, 4}, {3, 1, 3}
	//B_3 = {3, 1, 4}
	//E_3 = {1, 1, 2}, {2, 1, 1}, {3, 0, 0}
	//Ds_3 = {1, 1, 2}, {2, 1, 1}
	const Layer first(Note::C_3, Duration::Whole, note_mapper);
	const Layer second(Note::E_3, Duration::Whole, note_mapper);
	const Layer third(Note::Gs_3, Duration::Whole, note_mapper);
	const Layer fourth(Note::G_3, Duration::Whole, note_mapper);
	const Layer fifth(Note::A_3, Duration::Whole, note_mapper);
	const Layer sixth(Note::B_3, Duration::Whole, note_mapper);
	const Layer seventh(Note::E_3, Duration::Whole, note_mapper);
	const Layer eigth(Note::Ds_3, Duration::Whole, note_mapper);

	LayerList<out_type> l_list({first, second, third, fourth, fifth, sixth, seventh, eigth});
	l_list.buildTransitions(i.getActionSet());			
	
	const PhysAttrMap sol_1({1, 0, 0});
	const PhysAttrMap sol_2({2, 1, 1});
	const PhysAttrMap sol_3({3, 1, 2});
	const PhysAttrMap sol_4({3, 1, 2});
	const PhysAttrMap sol_5({3, 1, 3});
	const PhysAttrMap sol_6({3, 1, 4});
	const PhysAttrMap sol_7({2, 1, 1});
	const PhysAttrMap sol_8({2, 1, 1});

	const int cost_1 = 3;
	const int cost_2 = 2;
	const int cost_3 = 1;
	const int cost_4 = 2;
	const int cost_5 = 2;
	const int cost_6 = 4;
	const int cost_7 = 1;
	const int cost_8 = -1;
	
	solver->solve(l_list);
	int count = 0;
	for (auto sol : solver->getSolution()) {
		if (count == 0) {
			ASSERT_EQ(get<0>(sol).getState(), sol_1);
			ASSERT_EQ(get<1>(sol), cost_1);
		} else if (count == 1) {
			ASSERT_EQ(get<0>(sol).getState(), sol_2);
			ASSERT_EQ(get<1>(sol), cost_2);
		} else if (count == 2) {
			ASSERT_EQ(get<0>(sol).getState(), sol_3);
			ASSERT_EQ(get<1>(sol), cost_3);
		} else if (count == 3) {
			ASSERT_EQ(get<0>(sol).getState(), sol_4);
			ASSERT_EQ(get<1>(sol), cost_4);
		} else if (count == 4) {
			ASSERT_EQ(get<0>(sol).getState(), sol_5);
			ASSERT_EQ(get<1>(sol), cost_5);
		} else if (count == 5) {
			ASSERT_EQ(get<0>(sol).getState(), sol_6);
			ASSERT_EQ(get<1>(sol), cost_6);
		} else if (count == 6) {
			ASSERT_EQ(get<0>(sol).getState(), sol_7);
			ASSERT_EQ(get<1>(sol), cost_7);
		} else if (count == 7) {
			ASSERT_EQ(get<0>(sol).getState(), sol_8);
			ASSERT_EQ(get<1>(sol), cost_8);
		}
		count++;
	}
}
