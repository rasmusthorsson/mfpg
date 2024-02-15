#include "BasicNoteMapper.h"

using namespace noteenums;
using namespace std;
using iter = multimap<Note, tuple<int, int, int>>::iterator;

BasicNoteMapper::BasicNoteMapper(initializer_list<IString> strings) {
	mapped_notes.insert({noteenums::Note::REST, {0, 0, 0}});
	for (IString s : strings) {
		mapString(s);
	}

}
//For each string, create a map of notes to tuples.
BasicNoteMapper::BasicNoteMapper(vector<IString> strings) {
	mapped_notes.insert({noteenums::Note::REST, {0, 0, 0}});
	for (IString s : strings) {
		mapString(s);
	}
}

//Stringmapper for individual string.
void BasicNoteMapper::mapString(IString s) {
	using namespace noteenums;
	
	const int string_position = s.getPosition();
	const vector<Note> playable_notes = s.getPlayable();
	const int notes = playable_notes.size() - 2;
	
	//First note is always played on an empty string
	mapped_notes.insert(make_pair(s.getNote(0), make_tuple(string_position, 
									0, 0)));

	//For each note we construct a 3-tuple of each playable combination on the 
	//string. (String position (constant here), hand position, finger position), 
	//hand position and finger positions are linked inversely, increase in hand 
	//position decreases finger position.
	for (int note = 0; note <= notes; note = note + 2) {
		//Note base_note = s.getNote(note + 1);
		//Note half_up_note = s.getNote(note + 2);

		//Lowest hand position is either position 1 or note position - 3.
		const int lowest_hand_position = max(1, ((note / 2) + 1) - 3);
		
		//Highest hand position is either highest allowed note on the 
		//string - 3, or note position.
		const int highest_hand_position = min((note / 2) + 1, 
						      ((notes / 2) + 1) - 3);
		
		//Which fingers can be used are calculated using note position - lowest
		//hand position. This also gives us the highest finger which can play 
		//the note, allowing us to decrease in step with the increase in hand 
		//position to create correct combinations of the 3-tuple.
		int fingers = (note / 2) + 1 - lowest_hand_position + 1;
		for (int hand_position = lowest_hand_position; hand_position <= 
					highest_hand_position; hand_position++){
				const tuple<int, int, int> t_first = make_tuple(
								string_position, 
								hand_position, 
								fingers);
				mapped_notes.insert(make_pair(s.getNote(note + 1), 
									t_first));
			if (note != notes) { //Check for uneven amount of notes
						  //on a string to avoid out of bounds.
				const tuple<int, int, int> t_second = make_tuple(
							string_position, 
							hand_position, 
							fingers);
				mapped_notes.insert(make_pair(s.getNote(note + 2), 
									t_second));
			}
			fingers--;
		}
	}
}
