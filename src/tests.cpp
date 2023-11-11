#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ConversionException.h"
#include "BasicNoteMapper.h"
#include "LayerList.h"

//Tests valid construction of a simplified note.
TEST(SimplifiedNote, ValidInputs) {
	using namespace mx::api;
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

//Tests that construction of IString using ranged ints results in the correct notes being added.
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

//Tests that the construction of IString using noteenums results in the correct notes being added.
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

//Tests that the basic notemapper returns the correct amount of notes and amount of combinations
//according to the specifications.
TEST_F(NoteMapper_Tests, ValidNotes) {
        using namespace noteenums;	
	std::vector<IString> strings = {s1, s2};
	NoteMapper<std::tuple<int, int, int>>* map = new BasicNoteMapper(strings);
	int noteCount = 0;
	for (auto i = map->begin(), end = map->end(); i != end; 
			i = map->getUpper(i->first)) {
		noteCount++;
	}
	for (auto elem : map->getMap()) {
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
	ASSERT_EQ(map->size(), 30);
}

//Verify that all combinations constructed for 3 notes in the notemapper are the valid combinations
//for those notes.
TEST_F(NoteMapper_Tests, SampleTests) {
	using namespace noteenums;
	using namespace mx::api;
	std::vector<IString> strings = {s1, s2};
	NoteMapper<std::tuple<int, int, int>>* map = new BasicNoteMapper(strings);
	auto C3 = map->getRange(Note::C_3);
	auto E3 = map->getRange(Note::E_3);
	auto As_3 = map->getRange(Note::As_3);
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
	using namespace testing;
	std::vector<IString> strings = {s1, s2};
	NoteMapper<std::tuple<int, int, int>>* map = new BasicNoteMapper(strings);
	for (auto i = map->begin(); i != map->end(); i++) {
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
	Action<std::tuple<int, int, int>, int> NOC(d_f, "NOC");
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
	Action<std::tuple<int, int, int, bool, float>, float> UpstrokeDistance(d_f, "UD");
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
			SimplifiedNote note(n);
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

//Adding duplicate node results in -1.
TEST_F(Layer_Tests, AddSameNodeTwice) {
	using namespace mx::api;
	typedef std::tuple<int, int, int> ret;

	ret first{1, 1, 1};
	ret second{1, 1, 1};
	EXPECT_EQ(l.addNode(first), 1);
	ASSERT_EQ(l.addNode(second), -1);
}

//Failure to remove non-existant node returns -1.
TEST_F(Layer_Tests, RemoveNonexistantNode) {
	using namespace mx::api;
	typedef std::tuple<int, int, int> ret;
	
	ret first{1, 1, 1};	
	ret second{2, 2, 2};
	EXPECT_EQ(l.addNode(first), 1);
	ASSERT_EQ(l.removeNode(second), -1);
}

class ActionSet_Tests : public ::testing::Test {
	using in_type = std::tuple<unsigned int, unsigned int, unsigned int>;
	using out_type = int;
	typedef out_type (*a_type)(in_type, in_type);
	public:
		ActionSet<in_type, out_type> set;	
		ActionSet_Tests() {		
			a_type fingerAction = [] (in_type s1, in_type s2) {
				out_type finger = 
					std::max(std::get<2>(s1), std::get<2>(s2))
					- std::min(std::get<2>(s1), std::get<2>(s2));
				return finger;
			};
			
			a_type handAction = [] (in_type s1, in_type s2) {
				out_type hand = 
					std::max(std::get<1>(s1), std::get<1>(s2))
					- std::min(std::get<1>(s1), std::get<1>(s2));
				return hand;
			};
			
			a_type stringAction = [] (in_type s1, in_type s2) {
				out_type string = 
					std::max(std::get<0>(s1), std::get<0>(s2))
					- std::min(std::get<0>(s1), std::get<0>(s2));
				return string;
			};

			Action<in_type, out_type> f_a(fingerAction, "FA");
			Action<in_type, out_type> h_a(handAction, "HA");
			Action<in_type, out_type> s_a(stringAction, "SA");

			ActionSet<in_type, out_type> actions{{f_a, true}, {h_a, true}, 
				{s_a, true}};
			set = actions;
		}
};

//Checks that the ActionSet contains the correct actions.
TEST_F(ActionSet_Tests, CorrectActions) {
	using out_type = int;	
	int count = 0;
	for (auto a : set.getActions()) {
		count++;
	}
	ASSERT_EQ(std::get<0>(set.getActions()[0]).getID(), "FA");
	ASSERT_EQ(std::get<0>(set.getActions()[1]).getID(), "HA");
	ASSERT_EQ(std::get<0>(set.getActions()[2]).getID(), "SA");
	ASSERT_EQ(count, 3);
}

//Checks that the distance between different inputs corresponds with the actions in the
//ActionSet
TEST_F(ActionSet_Tests, CorrectDistance) {
	using in_type = std::tuple<unsigned int, unsigned int, unsigned int>;
	in_type f1 = {0, 0, 0};
	in_type s1 = {1, 2, 1};
	ASSERT_EQ(set.apply(f1, s1), 4);
	in_type f2 = {2, 2, 2};
	in_type s2 = {0, 3, 2};
	ASSERT_EQ(set.apply(f2, s2), 3);
}

//Check that dependencies accurately disable actions and cannot re-enable them.
TEST_F(ActionSet_Tests, Dependencies) {
	using in_type = std::tuple<unsigned int, unsigned int, unsigned int>;
	set.addDependency("HA", "FA", false);
	in_type f1 = {0, 0, 0};
	in_type s1 = {1, 10, 1};
	ASSERT_EQ(set.apply(f1, s1), 2);	
	set.addDependency("SA", "FA", false);
	ASSERT_EQ(set.apply(f1, s1), 1);	
	set.addDependency("SA", "FA", true);
	ASSERT_EQ(set.apply(f1, s1), 1);	
}


//Creates a LayerList of 4 layers corresponding to a sequence of notes combined with a basic 
//notemapper, then verifies that the layerlist does indeed contain all layers and that all
//layers have the correct amount of nodes.

//TODO Optimize object creations.

class LayerList_Tests : public ::testing::Test {
	using in_type = std::tuple<int, int, int>;
	private:
		LayerList<in_type, int> BuildLayerList() {
			using namespace noteenums;
			
			using in_type = std::tuple<int, int, int>;
			using out_type = int;
			typedef int (*a_type)(in_type, in_type);

			IString s1(1, Note::C_3, Note::B_3);
			IString s2(2, Note::G_3, Note::Ds_4);
			std::vector<IString> sv{s1, s2};

			NoteMapper<in_type>* notemap = new BasicNoteMapper(sv);

			SimplifiedNote d_s(Note::D_3, Duration::Whole);
			Layer<in_type> first(d_s, notemap);

			SimplifiedNote f_s(Note::Fs_3, Duration::Whole);
			Layer<in_type> second(f_s, notemap);
			
			SimplifiedNote g_s(Note::G_3, Duration::Whole);
			Layer<in_type> third(g_s, notemap);
			
			SimplifiedNote cs_s(Note::Cs_4, Duration::Whole);
			Layer<in_type> fourth(cs_s, notemap);

			LayerList<in_type, int> l1(first);
			l1.pushBack(second);
			l1.pushBack(third);
			l1.pushBack(fourth);

			a_type fingerAction = [] (in_type s1, in_type s2) {
				out_type finger = 
					std::max(std::get<2>(s1), std::get<2>(s2))
					- std::min(std::get<2>(s1), std::get<2>(s2));
				return finger;
			};
			
			a_type handAction = [] (in_type s1, in_type s2) {
				out_type hand = 
					std::max(std::get<1>(s1), std::get<1>(s2))
					- std::min(std::get<1>(s1), std::get<1>(s2));
				return hand;
			};
			
			a_type stringAction = [] (in_type s1, in_type s2) {
				out_type string = 
					std::max(std::get<0>(s1), std::get<0>(s2))
					- std::min(std::get<0>(s1), std::get<0>(s2));
				return string;
			};

			Action<in_type, out_type> f_a(fingerAction, "FA");
			Action<in_type, out_type> h_a(handAction, "HA");
			Action<in_type, out_type> s_a(stringAction, "SA");

			ActionSet<in_type, out_type> actions{{f_a, true}, {h_a, true}, 
				{s_a, true}};
			l1.buildTransitions(actions);
			return l1;
		}
	public:
		LayerList<in_type, int> list;
		LayerList_Tests() : list(BuildLayerList()) {}
};

TEST_F(LayerList_Tests, CountAndLayerCount) {
	int count = 0;
	for (auto l : list) {
		count++;
	}
	ASSERT_EQ(count, 4);
	auto l_it = list.begin();
	ASSERT_EQ(l_it++->getSize(), 2);
	ASSERT_EQ(l_it++->getSize(), 3);
	ASSERT_EQ(l_it++->getSize(), 4);
	ASSERT_EQ(l_it++->getSize(), 2);
}

TEST_F(LayerList_Tests, Transitions) {
	//C_3 - B_3 
	//G_3 - Ds_4
	//D_3 - Fs_3 - G_3 - Cs_3
	//TODO Calculate tuple combos
}

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

	NoteList notes(score);
	
	LayerList<std::tuple<int, int, int>, int> l1(notes);
	
	int count = 0;
	
	for (auto l : l1) {
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

//TODO Add layerlist actionset test for full transition check.

