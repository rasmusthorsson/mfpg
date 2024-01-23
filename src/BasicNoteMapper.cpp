#include "BasicNoteMapper.h"

using namespace noteenums;
using iter = std::multimap<Note, std::tuple<int, int, int>>::iterator;

BasicNoteMapper::BasicNoteMapper(std::initializer_list<IString> strings) {
	mappedNotes.insert({noteenums::Note::REST, {0, 0, 0}});
	for (IString s : strings) {
		mapString(s);
	}

}
//For each string, create a map of notes to tuples.
BasicNoteMapper::BasicNoteMapper(std::vector<IString> strings) {
	mappedNotes.insert({noteenums::Note::REST, {0, 0, 0}});
	for (IString s : strings) {
		mapString(s);
	}
}

//Stringmapper for individual string.
void BasicNoteMapper::mapString(IString s) {
	using namespace noteenums;
	
	int stringPosition = s.getPosition();
	std::vector<Note> playableNotes = s.getPlayable();
	int notes = playableNotes.size() - 1;
		
	//For each note we construct a 3-tuple of each playable combination on the 
	//string. (String position (constant here), hand position, finger position), 
	//hand position and finger positions are linked inversely, increase in hand 
	//position decreases finger position.
	for (int note = 0; note <= notes; note = note + 2) {

		//Lowest hand position is either position 1 or note position - 3.
		int lowestHandPosition = std::max(1, ((note / 2) + 1) - 3);
		
		//Highest hand position is either highest allowed note on the 
		//string - 3, or note position.
		int highestHandPosition = std::min((note / 2) + 1, 
						  ((notes / 2) + 1) - 3);
		
		//Which fingers can be used are calculated using note position - lowest
		//hand position. This also gives us the highest finger which can play 
		//the note, allowing us to decrease in step with the increase in hand 
		//position to create correct combinations of the 3-tuple.
		int fingers = (note / 2) + 1 - lowestHandPosition + 1;
		for (int handPosition = lowestHandPosition; handPosition <= 
					highestHandPosition; handPosition++){
				std::tuple<int, int, int> t_first = std::make_tuple(
								stringPosition, 
								handPosition, 
								fingers);
				mappedNotes.insert(std::make_pair(s.getNote(note), 
									t_first));
			if (note != notes) { //Check for uneven amount of notes
						  //on a string to avoid out of bounds.
				std::tuple<int, int, int> t_second = std::make_tuple(
							stringPosition, 
							handPosition, 
							fingers);
				mappedNotes.insert(std::make_pair(
							s.getNote(note+1), t_second));
			}
			fingers--;
		}
	}
}
