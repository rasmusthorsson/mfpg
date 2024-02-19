#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ConversionException.h"
#include "BasicNoteMapper.h"
#include "GreedySolver.h"
#include "Instrument.h"
#include "SolverException.h"

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

	auto note_itr = notes.begin();
	
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

	unique_ptr<NoteMapper<tuple<int, int, int>>>map(new BasicNoteMapper({s1, s2}));

	int note_count = 0;
	for (auto i = map->begin(), end = map->end(); i != end;
		  i = map->getUpper(i->first)) {
		note_count++;
	}

	for (auto& elem : map->getMap()) {
		cout << "Note: " << elem.first << "\n";
		cout << "String: " << get<0>(elem.second)
			<< " HP: " << get<1>(elem.second)
			<< " Finger: " << get<2>(elem.second) << "\n";
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

	unique_ptr<NoteMapper<tuple<int, int, int>>>map(new BasicNoteMapper({s1, s2}));

	auto C3 = map->getRange(Note::C_3);
	auto D_3 = map->getRange(Note::D_3);
	auto E3 = map->getRange(Note::E_3);
	auto As_3 = map->getRange(Note::As_3);

	int comb_count = 0;
	//Check valid combinations for C_3.
	for (auto i = C3.first; i != C3.second; i++) {
		comb_count++;
		if (comb_count == 1) {
			ASSERT_EQ(get<0>(i->second), 1);
			ASSERT_EQ(get<1>(i->second), 0);
			ASSERT_EQ(get<2>(i->second), 0);
		}
	}
	//Check valid combinations for D_3.
	for (auto i = D_3.first; i != D_3.second; i++) {
		comb_count++;
		if (comb_count == 2) {
			ASSERT_EQ(get<0>(i->second), 1);
			ASSERT_EQ(get<1>(i->second), 1);
			ASSERT_EQ(get<2>(i->second), 1);
		}
	}
	//Check valid combinations for E_3.
	for (auto i = E3.first; i != E3.second; i++) {
		comb_count++;
		if (comb_count == 3) {
			ASSERT_EQ(get<0>(i->second), 1);
			ASSERT_EQ(get<1>(i->second), 1);
			ASSERT_EQ(get<2>(i->second), 2);
		} else if (comb_count == 4) {
			ASSERT_EQ(get<0>(i->second), 1);
			ASSERT_EQ(get<1>(i->second), 2);
			ASSERT_EQ(get<2>(i->second), 1);
		} else if (comb_count == 5) {
			ASSERT_EQ(get<0>(i->second), 2);
			ASSERT_EQ(get<1>(i->second), 1);
			ASSERT_EQ(get<2>(i->second), 1);
		}
	}
	//Check valid combinations for As_3.
	for (auto i = As_3.first; i != As_3.second; i++) {
		comb_count++;
		if (comb_count == 6) {
			ASSERT_EQ(get<0>(i->second), 2);
			ASSERT_EQ(get<1>(i->second), 1);
			ASSERT_EQ(get<2>(i->second), 4);
		} else if (comb_count == 7) {
			ASSERT_EQ(get<0>(i->second), 2);
			ASSERT_EQ(get<1>(i->second), 2);
			ASSERT_EQ(get<2>(i->second), 3);
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

	unique_ptr<NoteMapper<tuple<int, int, int>>> 
		map(new BasicNoteMapper({s1, s2}));

	for (auto i = map->begin(); i != map->end(); i++) {
		if (i->first != Note::REST) {
			ASSERT_THAT(get<0>(i->second), AllOf(Lt(3), Gt(0)));
			ASSERT_THAT(get<1>(i->second), AllOf(Lt(3), Gt(-1)));
			ASSERT_THAT(get<2>(i->second), AllOf(Lt(5), Gt(-1)));
		} else {
			ASSERT_THAT(get<2>(i->second), AllOf(Lt(1), Gt(-1)));
		}
	}
}
//Tests that a basic action using a 3-tuple with an int return returns the proper
//distance and condition.
TEST(Action, BasicAction) {
	using namespace std;

	using Input_Tuple = tuple<int, int, int>;

	typedef bool (*a_type_cond)(Input_Tuple, Input_Tuple);
	typedef int (*a_type_dist)(Input_Tuple, Input_Tuple);

	a_type_cond d_f_cond = [] (Input_Tuple t1, Input_Tuple t2) {
		return true;
	};
	a_type_dist d_f_dist = [] (Input_Tuple t1, Input_Tuple t2) {
		int string = abs(get<0>(t1) - get<0>(t2));
		int hand = abs(get<1>(t1) - get<1>(t2));
		int finger = abs(get<2>(t1) - get<2>(t2));
		return string + hand + finger;	
	};
	const Action<Input_Tuple, int> NOC(d_f_cond, d_f_dist, "NOC");

	const Input_Tuple t1{1, 1, 1};
	const Input_Tuple t2{2, 2, 2};

	ASSERT_EQ(NOC.distance(t1, t2), 3);
	ASSERT_EQ(NOC.condition(t1, t2), true);
}

//Tests that a more complex action using floats and booleans returns the correct
//distance and condition.
TEST(Action, FiveTupleAction) {
	using namespace std;
	using Input_Tuple = tuple<int, int, int, bool, float>;

	typedef bool (*a_type_cond)(Input_Tuple, Input_Tuple);
	typedef float (*a_type_dist)(Input_Tuple, Input_Tuple);

	a_type_dist d_f_dist = [] (Input_Tuple s1, Input_Tuple s2) {
		int string = abs(get<0>(s1) - get<0>(s2));
		int hand = abs(get<1>(s1) - get<1>(s2));
		int finger = abs(get<2>(s1) - get<2>(s2));
		int up_stroke = get<3>(s1) || get<3>(s2);
		float note_distance = abs(get<4>(s1) - get<4>(s2));
		float res;

	       	if (up_stroke) {
			res = (string + hand + finger) * note_distance;
		} else{
			res = (string + hand + finger);
		}
		return static_cast<float>(res);
	};
	a_type_cond d_f_cond = [] (Input_Tuple s1, Input_Tuple s2) {
		return true;
	};
	const Action<Input_Tuple, float> upstroke_distance(d_f_cond, d_f_dist, "UD");

	const Input_Tuple t1(1, 2, 1, false, 3.0);
	const Input_Tuple t2(1, 2, 3, false, 7.0);
	const Input_Tuple t3(1, 2, 1, true, 3.0);
	const Input_Tuple t4(1, 2, 3, false, 7.0);

	ASSERT_EQ(upstroke_distance.distance(t1, t2), 2.0);
	ASSERT_EQ(upstroke_distance.distance(t3, t4), 8.0);
}

class Layer_Tests : public ::testing::Test {
	typedef std::tuple<int, int, int> ret;
	public:
		Layer_Tests() : l(noteenums::Note::C_3, noteenums::Duration::Whole) {}
		void SetUp() override {
			l.clear();
		}
		void TearDown() override {
			l.clear();
		}
		Layer<ret> l;
};

//Tests that creating a basic layer using add and remove results in the correct
//tuples are being added and removed.
TEST_F(Layer_Tests, BasicLayer) {
	using namespace mx::api;
	typedef std::tuple<int, int, int> ret;
	
	const ret first{1, 1, 1};

	EXPECT_NO_THROW(l.addNode(first));
	ASSERT_EQ(l.getSize(), 1);

	const ret second{2, 1, 1};

	EXPECT_NO_THROW(l.addNode(second));
	ASSERT_EQ(l.getSize(), 2);
	EXPECT_NO_THROW(l.removeNode(first));
	ASSERT_EQ(l.getSize(), 1);

	const ret third{1, 2, 1};

	EXPECT_NO_THROW(l.addNode(third));
	ASSERT_EQ(l.getSize(), 2);

	const ret fourth{1, 1, 2};

	EXPECT_NO_THROW(l.addNode(fourth));
	ASSERT_EQ(l.getSize(), 3);
	EXPECT_NO_THROW(l.removeNode(fourth));
	ASSERT_EQ(l.getSize(), 2);
}

//Tests that adding a duplicate node results in -1 and fails to add the second 
//node while retaining first node.
TEST_F(Layer_Tests, AddSameNodeTwice) {
	using namespace mx::api;

	typedef std::tuple<int, int, int> ret;

	const ret first{1, 1, 1};
	const ret second{1, 1, 1};

	EXPECT_EQ(l.addNode(first), 1);
	ASSERT_EQ(l.addNode(second), -1);
	ASSERT_EQ(l.getSize(), 1);
	ASSERT_EQ(l[0], first);
}

//Tests that failure to remove a non-existant node returns -1 and retains first node.
TEST_F(Layer_Tests, RemoveNonexistantNode) {
	using namespace mx::api;
	typedef std::tuple<int, int, int> ret;
	
	const ret first{1, 1, 1};	
	const ret second{2, 2, 2};

	EXPECT_EQ(l.addNode(first), 1);
	ASSERT_EQ(l.removeNode(second), -1);
	ASSERT_EQ(l.getSize(), 1);
	ASSERT_EQ(l[0], first);
}

class ActionSet_Tests : public ::testing::Test {
	using in_type = std::tuple<int, int, int>;
	using out_type = int;

	typedef out_type (*a_type_dist)(in_type, in_type);
	typedef bool (*a_type_cond)(in_type, in_type);

	public:
		std::unique_ptr<ActionSet<in_type, out_type>> set;
		ActionSet_Tests() {		
			using namespace std;

			a_type_cond fa_cond = [] (in_type s1, in_type s2) {
				return true;
			};
			a_type_dist fa_dist = [] (in_type s1, in_type s2) {
				return max(get<2>(s1), get<2>(s2))
				       - min(get<2>(s1), get<2>(s2));
			};
			const Action<in_type, out_type> f_a(fa_cond, fa_dist, "FA");
			
			a_type_cond ha_cond = [] (in_type s1, in_type s2) {
				return true;
			};
			a_type_dist ha_dist = [] (in_type s1, in_type s2) {
				return max(get<1>(s1), get<1>(s2))
					 - min(get<1>(s1), get<1>(s2));
			};
			const Action<in_type, out_type> h_a(ha_cond, ha_dist, "HA");
			
			a_type_cond sa_cond = [] (in_type s1, in_type s2) {
				return true;
			};
			a_type_dist sa_dist = [] (in_type s1, in_type s2) {
				return max(get<0>(s1), get<0>(s2))
					- min(get<0>(s1), get<0>(s2));
			};
			const Action<in_type, out_type> s_a(sa_cond, sa_dist, "SA");

			set = unique_ptr<ActionSet<in_type, out_type>>(new ActionSet<in_type, out_type>{
							{f_a, true}, 
							{h_a, true}, 
							{s_a, true}
							});
		}
};

//Tests that the distance between different inputs corresponds with the actions in 
//the ActionSet
TEST_F(ActionSet_Tests, CorrectDistance) {
	using in_type = std::tuple<unsigned int, unsigned int, unsigned int>;

	const in_type f1 = {0, 0, 0};
	const in_type s1 = {1, 2, 1};

	ASSERT_EQ(set->apply(f1, s1), 4);

	const in_type f2 = {2, 2, 2};
	const in_type s2 = {0, 3, 2};

	ASSERT_EQ(set->apply(f2, s2), 3);
}

//Tests that dependencies correctly disable actions and cannot re-enable them.
TEST_F(ActionSet_Tests, Dependencies) {
	using in_type = std::tuple<unsigned int, unsigned int, unsigned int>;

	set->addDependency("HA", "FA", false);

	const in_type f1 = {0, 0, 0};
	const in_type s1 = {1, 10, 1};

	ASSERT_EQ(set->apply(f1, s1), 2);	

	set->addDependency("SA", "FA", false);

	ASSERT_EQ(set->apply(f1, s1), 1);	

	set->addDependency("SA", "FA", true);

	ASSERT_EQ(set->apply(f1, s1), 1);	
}

class LayerList_Tests : public ::testing::Test {
	using in_type = std::tuple<int, int, int>;
	using out_type = int;

	public:
		std::unique_ptr<LayerList<in_type, int>> list;
		LayerList_Tests() {
			using namespace noteenums;
			using namespace std;

			typedef out_type (*a_type_dist) (in_type, in_type);
			typedef bool (*a_type_cond) (in_type, in_type);

			const IString s1(1, Note::C_3, Note::B_3);
			const IString s2(2, Note::G_3, Note::Ds_4);

			std::shared_ptr<NoteMapper<in_type>> note_mapper(new BasicNoteMapper({s1, s2}));

			const Layer<in_type> first(Note::D_3, Duration::Whole, note_mapper);
			const Layer<in_type> second(Note::Fs_3, Duration::Whole, note_mapper);
			const Layer<in_type> third(Note::G_3, Duration::Whole, note_mapper);
			const Layer<in_type> fourth(Note::Cs_4, Duration::Whole, note_mapper);

			vector<Layer<in_type>> l_vec({first, second, third, fourth});

			list = unique_ptr<LayerList<in_type, int>>(new LayerList<in_type, out_type>(l_vec));

			a_type_cond fa_cond = [] (in_type s1, in_type s2) {
				return true;
			};
			a_type_dist fa_dist = [] (in_type s1, in_type s2) {
				return max(get<2>(s1), get<2>(s2))
					- min(get<2>(s1), get<2>(s2));
			};
			const Action<in_type, out_type> f_a(fa_cond, fa_dist, "FA");
			
			a_type_cond ha_cond = [] (in_type s1, in_type s2) {
				return true;
			};
			a_type_dist ha_dist = [] (in_type s1, in_type s2) {
				return max(get<1>(s1), get<1>(s2))
					- min(get<1>(s1), get<1>(s2));
			};
			const Action<in_type, out_type> h_a(ha_cond, ha_dist, "HA");
			
			a_type_cond sa_cond = [] (in_type s1, in_type s2) {
				return true;
			};
			a_type_dist sa_dist = [] (in_type s1, in_type s2) {
				return max(get<0>(s1), get<0>(s2))
					- min(get<0>(s1), get<0>(s2));
			};
			const Action<in_type, out_type> s_a(sa_cond, sa_dist, "SA");

			std::shared_ptr<ActionSet<in_type, out_type>> actions(
							new ActionSet<in_type, out_type>{
							    {f_a, true}, 
							    {h_a, true}, 
							    {s_a, true}
							    });

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

	ASSERT_EQ(l_it++->getSize(), 1);
	ASSERT_EQ(l_it++->getSize(), 3);
	ASSERT_EQ(l_it++->getSize(), 4);
	ASSERT_EQ(l_it++->getSize(), 1);
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
	for (auto& transition : l_it->getTransitions()) {
		cout << get<0>(transition.first) << ", ";
		cout << get<1>(transition.first) << ", ";
		cout << get<2>(transition.first) << "\n";
		for (auto& output : transition.second) {
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
	for (auto& transition : l_it->getTransitions()) {
		cout << get<0>(transition.first) << ", ";
		cout << get<1>(transition.first) << ", ";
		cout << get<2>(transition.first) << "\n";
		for (auto& output : transition.second) {
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
	for (auto& transition : l_it->getTransitions()) {
		cout << get<0>(transition.first) << ", ";
		cout << get<1>(transition.first) << ", ";
		cout << get<2>(transition.first) << "\n";
		for (auto& output : transition.second) {
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
	for (auto& transition : l_it->getTransitions()) {
		for (auto& output : transition.second) {
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

	std::shared_ptr<NoteMapper<std::tuple<int, int, int>>>note_mapper(new BasicNoteMapper());
	
	LayerList<std::tuple<int, int, int>, int> l1(notes, note_mapper);
	
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

class GreedySolver_Tests : public ::testing::Test {
	using in_type = std::tuple<int, int, int>;
	using out_type = int;

	private:
		Instrument<in_type, out_type> buildInstrument() {
			using namespace std;

			typedef out_type (*action_type_dist)(in_type, in_type);
			typedef bool (*action_type_cond)(in_type, in_type);

			const IString s1(1, Note::C_3, Note::G_3);
			const IString s2(2, Note::D_3, Note::A_3);
			const IString s3(3, Note::E_3, Note::B_3);
			
			std::shared_ptr<NoteMapper<in_type>> note_mapper(new BasicNoteMapper({s1, s2, s3}));

			action_type_cond action_cond = [] (in_type t1, in_type t2) {
				return true;
			};
			action_type_dist action_dist = [] (in_type t1, in_type t2) {
				int out = abs(get<1>(t1) - get<1>(t2));
				out = out + abs(get<2>(t1) - get<2>(t2));
				if (abs(get<0>(t1) - get<0>(t2)) >= 2) {
					out = out + 100;
				} else {
					out = out + 1;
				}
				return out;
			};
			const Action<in_type, out_type> a1(action_cond, 
							   action_dist, 
							   "A1");
			
			std::shared_ptr<ActionSet<in_type, out_type>> set(
						new ActionSet<in_type, out_type>({a1, true}));

			const vector<IString> sv{s1, s2, s3};
			const Instrument<in_type, out_type> i(sv, note_mapper, set);

			return i;
		}
	public:
		GreedySolver_Tests() : instrument(buildInstrument()) {}
		const Instrument<in_type, out_type> instrument;
};

//Tests that the greedysolver selects the correct path and outputs the correct costs.
TEST_F(GreedySolver_Tests, Basic) {
	using namespace noteenums;
	using namespace std;

	using in_type = tuple<int, int, int>;
	using out_type = int;	
	
	std::unique_ptr<GraphSolver<in_type, out_type>> solver(new GreedySolver());
	
	const Layer<in_type> first(Note::C_3, Duration::Whole, instrument.getNoteMapper());
	const Layer<in_type> second(Note::E_3, Duration::Whole, instrument.getNoteMapper());
	const Layer<in_type> third(Note::Gs_3, Duration::Whole, instrument.getNoteMapper());

	LayerList<in_type, out_type> l_list({first, second, third});
	l_list.buildTransitions(instrument.getActionSet());			

	solver->solve(l_list);

	//C_3 = {1, 0, 0}
	//E_3 = {2, 1, 1}, {3, 0, 0}
	//Gs_3 = {3, 1, 3}, {3, 1, 2}

	const in_type sol_1({1, 0, 0});
	const in_type sol_2({2, 1, 1});
	const in_type sol_3({3, 1, 2});

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
