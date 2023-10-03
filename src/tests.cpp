#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ConversionException.h"
#include "NoteList.h"
#include "BasicNoteMapper.h"
#include "LayerListException.h"

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
		EXPECT_EQ(ce.what(), "Note out of range.");
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
		EXPECT_EQ(ce.what(), "Note out of range.");
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
		EXPECT_EQ(ce.what(), "Duration not found.");
	}
}

//Assert that all notes added to a string are in the same order as the vector used to add them.
TEST(IString, SpecifiedNotes) {
	using namespace noteenums;
	Note C(Note::C_3);
	Note C_s(Note::Cs_3);
	Note D(Note::D_3);
	Note D_s(Note::Ds_3);
	Note E(Note::E_3);
	Note F(Note::F_3);
	Note F_s(Note::Fs_3);
	Note G(Note::G_3);
	Note G_s(Note::Gs_3);
	std::vector<Note> notes{C, C_s, D, D_s, E, F, F_s, G, G_s};
	IString s(1, notes);
	for (int i = 0; i < s.getPlayable().size(); i++) {
		ASSERT_EQ(s.getPlayable()[i], notes[i]);
	}
}

TEST(IString, RangedInts) {
	using namespace noteenums;
	Note C(Note::C_3);
	Note C_s(Note::Cs_3);
	Note D(Note::D_3);
	Note D_s(Note::Ds_3);
	Note E(Note::E_3);
	Note F(Note::F_3);
	Note F_s(Note::Fs_3);
	Note G(Note::G_3);
	Note G_s(Note::Gs_3);
	std::vector<Note> notes{C, C_s, D, D_s, E, F, F_s, G, G_s};
	IString s(1, 36, 44);
	for (int i = 0; i < s.getPlayable().size(); i++) {
		ASSERT_EQ(s.getPlayable()[i], notes[i]);
	}
}

TEST(IString, RangedNotes) {
	using namespace noteenums;
	Note C(Note::C_3);
	Note C_s(Note::Cs_3);
	Note D(Note::D_3);
	Note D_s(Note::Ds_3);
	Note E(Note::E_3);
	Note F(Note::F_3);
	Note F_s(Note::Fs_3);
	Note G(Note::G_3);
	Note G_s(Note::Gs_3);
	std::vector<Note> notes{C, C_s, D, D_s, E, F, F_s, G, G_s};
	IString s(1, Note::C_3, Note::Gs_3);
	for (int i = 0; i < s.getPlayable().size(); i++) {
		ASSERT_EQ(s.getPlayable()[i], notes[i]);
	}
}

//Tests an empty NoteList is the result of an empty score.
TEST(NoteList, Undefined) {
	using namespace mx::api;
	ScoreData score = ScoreData{};
	NoteList noteList(score);
	ASSERT_EQ(noteList.size(), 0);
}

//Test to make sure notes preserve their order when placed into a notelist from a score.
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

	NoteList notes(score);

	ASSERT_EQ(notes.size(), 5);
	ASSERT_EQ(notes.front().getNote(), Note::A_4);
	notes.pop_front();
	
	ASSERT_EQ(notes.size(), 4);
	ASSERT_EQ(notes.front().getNote(), Note::B_4);
	notes.pop_front();
	
	ASSERT_EQ(notes.size(), 3);
	ASSERT_EQ(notes.front().getNote(), Note::C_5);
	notes.pop_front();
	
	ASSERT_EQ(notes.size(), 2);
	ASSERT_EQ(notes.front().getNote(), Note::D_5);
	notes.pop_front();
	
	ASSERT_EQ(notes.size(), 1);
	ASSERT_EQ(notes.front().getNote(), Note::E_5);
	notes.pop_front();
}

class NoteMapper_Tests : public ::testing::Test {
	private:
		//Creates two strings with 9 playable notes each, the strings overlap on 
		//three notes.
		std::pair<IString, IString> createStrings() {
			using namespace std;
			using namespace noteenums;
			Note C(Note::C_3);
			Note C_s(Note::Cs_3);
			Note D(Note::D_3);
			Note D_s(Note::Ds_3);
			Note E(Note::E_3);
			Note F(Note::F_3);
			Note F_s(Note::Fs_3);
			Note G(Note::G_3);
			Note G_s(Note::Gs_3);
			Note A(Note::A_3);
			Note A_s(Note::As_3);
			Note B(Note::B_3);
			std::vector<Note> 
				notes_1{C, C_s, D, D_s, E, F, F_s, G, G_s};
			std::vector<Note> 
				notes_2{D_s, E, F, F_s, G, G_s, A, A_s, B};
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
        using namespace noteenums;	
	std::vector<IString> strings = {s1, s2};
	NoteMapper<std::tuple<int, int, int>>* map = new BasicNoteMapper(strings);
	auto m = map->getMap();
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
	ASSERT_EQ(noteCount, 12);
	ASSERT_EQ(m.size(), 30);
}

TEST_F(NoteMapper_Tests, SampleTests) {
	using namespace noteenums;
	using namespace mx::api;
	using namespace simplifiednote;
	std::vector<IString> strings = {s1, s2};
	NoteMapper<std::tuple<int, int, int>>* map = new BasicNoteMapper(strings);
	auto m = map->getMap();
	auto C3 = m.equal_range(Note::C_3);
	auto E3 = m.equal_range(Note::E_3);
	auto As_3 = m.equal_range(Note::As_3);
	int combCount = 0;
	//Check valid combinations for C_3.
	for (auto i = C3.first; i != C3.second; i++) {
		combCount++;
		if (combCount == 1) {
			ASSERT_EQ(std::get<0>(i->second), 1);
			ASSERT_EQ(std::get<1>(i->second), 1);
			ASSERT_EQ(std::get<2>(i->second), 1);
		}
	}
	//Check valid combinations for E_3.
	for (auto i = E3.first; i != E3.second; i++) {
		combCount++;
		if (combCount == 2) {
			ASSERT_EQ(std::get<0>(i->second), 1);
			ASSERT_EQ(std::get<1>(i->second), 1);
			ASSERT_EQ(std::get<2>(i->second), 3);
		} else if (combCount == 3) {
			ASSERT_EQ(std::get<0>(i->second), 1);
			ASSERT_EQ(std::get<1>(i->second), 2);
			ASSERT_EQ(std::get<2>(i->second), 2);
		} else if (combCount == 4) {
			ASSERT_EQ(std::get<0>(i->second), 2);
			ASSERT_EQ(std::get<1>(i->second), 1);
			ASSERT_EQ(std::get<2>(i->second), 1);
		}
	}
	//Check valid combinations for As_3.
	for (auto i = As_3.first; i != As_3.second; i++) {
		combCount++;
		if (combCount == 5) {
			ASSERT_EQ(std::get<0>(i->second), 2);
			ASSERT_EQ(std::get<1>(i->second), 1);
			ASSERT_EQ(std::get<2>(i->second), 4);
		} else if (combCount == 6) {
			ASSERT_EQ(std::get<0>(i->second), 2);
			ASSERT_EQ(std::get<1>(i->second), 2);
			ASSERT_EQ(std::get<2>(i->second), 3);
		} 
	}
	//Ensure there are no more unchecked combinations.
	ASSERT_EQ(combCount, 6);
}

//Check that only allowed strings, hand positions, and finger numbers are used.
TEST_F(NoteMapper_Tests, ValidPosition) {
	using namespace noteenums;
	using namespace mx::api;
	using namespace simplifiednote;
	using namespace testing;
	std::vector<IString> strings = {s1, s2};
	NoteMapper<std::tuple<int, int, int>>* map = new BasicNoteMapper(strings);
	auto m = map->getMap();
	for (auto i = m.begin(); i != m.end(); i++) {
		ASSERT_THAT(std::get<0>(i->second), AllOf(Lt(3), Gt(0)));
		ASSERT_THAT(std::get<1>(i->second), AllOf(Lt(3), Gt(0)));
		ASSERT_THAT(std::get<2>(i->second), AllOf(Lt(5), Gt(0)));
	}
}

//Definition of a basic action using a 3-tuple with an int return.
TEST(Action, BasicAction) {
	typedef int (*a_type)(std::tuple<int, int, int>, std::tuple<int, int, int>);
	a_type d_f = [] (std::tuple<int, int, int> s1, std::tuple<int, int, int> s2) {
		int string = std::abs(std::get<0>(s1) - std::get<0>(s2));
		int hand = std::abs(std::get<1>(s1) - std::get<1>(s2));
		int finger = std::abs(std::get<2>(s1) - std::get<2>(s2));
		return string + hand + finger;
	};
	Action<std::tuple<int, int, int>, int> NOC(d_f);
	std::tuple<int, int, int> t1{1, 1, 1};
	std::tuple<int, int, int> t2{2, 2, 2};
	ASSERT_EQ(NOC.distance(t1, t2), 3);
}

//More complex action, using floats and booleans.
TEST(Action, FiveTupleAction) {
	typedef float (*a_type)(std::tuple<int, int, int, bool, float>, 
			std::tuple<int, int, int, bool, float>);
	a_type d_f = [] (std::tuple<int, int, int, bool, float> s1, 
			std::tuple<int, int, int, bool, float> s2) {
		int string = std::abs(std::get<0>(s1) - std::get<0>(s2));
		int hand = std::abs(std::get<1>(s1) - std::get<1>(s2));
		int finger = std::abs(std::get<2>(s1) - std::get<2>(s2));
		int upStroke = std::get<3>(s1) || std::get<3>(s2);
		float noteDistance = std::abs(std::get<4>(s1) - std::get<4>(s2));
		float res;
	       	if (upStroke) {
			res = (string + hand + finger) * noteDistance;
		} else{
			res = (string + hand + finger);
		}
		return static_cast<float>(res);
	};
	Action<std::tuple<int, int, int, bool, float>, float> UpstrokeDistance(d_f);
	std::tuple<int, int, int, bool, float> t1(1, 2, 1, false, 3.0);
	std::tuple<int, int, int, bool, float> t2(1, 2, 3, false, 7.0);
	std::tuple<int, int, int, bool, float> t3(1, 2, 1, true, 3.0);
	std::tuple<int, int, int, bool, float> t4(1, 2, 3, false, 7.0);
	ASSERT_EQ(UpstrokeDistance.distance(t1, t2), 2.0);
	ASSERT_EQ(UpstrokeDistance.distance(t3, t4), 8.0);
}

class Layer_Tests : public ::testing::Test {
	typedef std::tuple<int, int, int> ret;
	
	private:
		Layer<ret> createLayer() {
			using namespace mx::api;
			NoteData n = NoteData{};
			n.durationData.durationName = DurationName::whole;
			n.pitchData.step = Step::c;
			n.pitchData.octave = 3;
			n.pitchData.alter = 0;
			simplifiednote::SimplifiedNote note(n);
			return Layer<ret>(n);
		}
	public:
		Layer_Tests() : l(createLayer()) {}
		void SetUp() override {
			l.clear();
		}
		void TearDown() override {
			l.clear();
		}
		Layer<ret> l;
};
//Simple test for creating a basic layer using add and remove.
TEST_F(Layer_Tests, BasicLayer) {
	using namespace mx::api;
	typedef std::tuple<int, int, int> ret;
	
	ret first{1, 1, 1};
	EXPECT_NO_THROW(l.addNode(first));
	ASSERT_EQ(l.getSize(), 1);
	ret second{2, 1, 1};
	EXPECT_NO_THROW(l.addNode(second));
	ASSERT_EQ(l.getSize(), 2);
	EXPECT_NO_THROW(l.removeNode(first));
	ASSERT_EQ(l.getSize(), 1);
	ret third{1, 2, 1};
	EXPECT_NO_THROW(l.addNode(third));
	ASSERT_EQ(l.getSize(), 2);
	ret fourth{1, 1, 2};
	EXPECT_NO_THROW(l.addNode(fourth));
	ASSERT_EQ(l.getSize(), 3);
	EXPECT_NO_THROW(l.removeNode(fourth));
	ASSERT_EQ(l.getSize(), 2);
}

//Attempting to add duplicate node to a layer results in an exception.
TEST_F(Layer_Tests, AddSameNodeTwice) {
	using namespace mx::api;
	typedef std::tuple<int, int, int> ret;

	ret first{1, 1, 1};
	ret second{1, 1, 1};
	EXPECT_NO_THROW(l.addNode(first));
	ASSERT_THROW(l.addNode(second), NodeException<ret>);
}

TEST_F(Layer_Tests, RemoveNonexistantNode) {
	using namespace mx::api;
	typedef std::tuple<int, int, int> ret;
	
	ret first{1, 1, 1};	
	ret second{2, 2, 2};
	EXPECT_NO_THROW(l.addNode(first));
	ASSERT_THROW({try {
			l.removeNode(second);
			} catch(NodeException<ret> e) {
				EXPECT_EQ( "Could not locate node in note layer.", e.what());
				throw;
			}
		}, NodeException<ret>);	
}

TEST(LayerList, Basic) {
	using namespace noteenums;

	simplifiednote::SimplifiedNote d_s(Note::D_3, Duration::Whole);
	Layer<std::tuple<int, int, int>> first(d_s);

	simplifiednote::SimplifiedNote f_s(Note::Fs_3, Duration::Whole);
	Layer<std::tuple<int, int, int>> second(f_s);
	
	simplifiednote::SimplifiedNote g_s(Note::G_3, Duration::Whole);
	Layer<std::tuple<int, int, int>> third(g_s);
	
	simplifiednote::SimplifiedNote cs_s(Note::Cs_3, Duration::Whole);
	Layer<std::tuple<int, int, int>> fourth(cs_s);

	IString s1(1, Note::C_3, Note::B_3);
	IString s2(2, Note::G_3, Note::Ds_4);
	std::vector<IString> sv{s1, s2};

	NoteMapper<std::tuple<int, int, int>>* notemap = new BasicNoteMapper(sv);
	auto map = notemap->getMap();
	auto range = map.equal_range(d_s.getNote());
	for (auto i = range.first; i != range.second; ++i) {
		first.addNode(i->second);
	}

	LayerList<std::tuple<int, int, int>, int> l_list1(first);
	ASSERT_EQ(l_list1.getElem().getSize(), 2);
}
