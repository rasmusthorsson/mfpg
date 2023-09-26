#include "BasicNoteMapper.h"

using namespace noteenums;

//For each string, create a map of notes to tuples.
BasicNoteMapper::BasicNoteMapper(std::vector<IString> strings) {
	for (IString s : strings) {
		mapString(s);
	}
}

//Stringmapper for individual string.
void BasicNoteMapper::mapString(IString s) {
	using namespace noteenums;
	
	int s_pos = s.getPosition();
	std::vector<Note> playableNotes = s.getPlayable();
	int notes = s.getPlayable().size() - 1;
	
	//For each note we construct a 3-tuple of each playable combination on the string.
	//(String position (constant here), hand position, finger position), hand position
	//and finger positions are linked inversely, increase in hand position decreases
	//finger position.
	for (int note = 0; note <= notes; note = note + 2) {

		//Lowest hand position is either position 1 or note position - 3.
		int lowest_hand_position = std::max(1, ((note / 2) + 1) - 3);
		
		//Highest hand position is either highest allowed note on the string - 3,
		//or note position.
		int highest_hand_position = std::min((note / 2) + 1, ((notes / 2) + 1) - 3);
		
		//Which fingers can be used are calculated using note position - lowest
		//hand position. This also gives us the highest finger which can play the
		//note, allowing us to decrease in step with the increase in hand position
		//below to create correct combinations of the 3-tuple.
		int fingers = (note / 2) + 1 - lowest_hand_position + 1;
		for (int hand_pos = lowest_hand_position; 
						hand_pos <= highest_hand_position; hand_pos++){
				std::tuple<int, int, int> t_first = 
				std::make_tuple(s_pos, hand_pos, fingers);
				mappedNotes.insert(std::make_pair(s.getNote(note), t_first));
			if (!(note == (notes))) { //Check for uneven amount of notes
						  //on a string to avoid out of bounds.
				std::tuple<int, int, int> t_second = 
				std::make_tuple(s_pos, hand_pos, fingers);
				mappedNotes.insert(std::make_pair(s.getNote(note+1), t_second));
			}
			fingers--;
		}
	}
}

std::multimap<noteenums::Note, std::tuple<int, int, int>> BasicNoteMapper::getMap() {
	return this->mappedNotes;
}


