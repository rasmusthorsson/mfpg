#include "NoteMapper.h"

using namespace noteenums;

NoteMapper::NoteMapper(std::vector<IString> strings) {
	for (IString s : strings) {
		mapString(s);
	}
}

//TODO Possible hand position constraints?
//TODO NEXT: Test, refractor, improve
void NoteMapper::mapString(IString s) {
	using namespace simplifiednote;
	int s_pos = s.getPosition();
	std::vector<SimplifiedNote> playableNotes = s.getPlayable();
	int notes = s.getPlayable().size() - 1;
	//For loop dictates hand position since each finger per hand position can play two notes
	for (int i = 0; i < notes; i = i + 2) { //TODO possible off by one
		int fingers = 4;
		int f_temp = fingers; //TODO Re-add functionality for fewer finger positions
				      //for low/high noters.
		//If i < 7 then we are treating one of the first 7 notes
		for (int j = (i / 2) + 1; j < (i / 2) + fingers + 1; j++) {
			std::tuple<int, int, int> t_first = 
				std::make_tuple(s_pos, j, f_temp);
			std::tuple<int, int, int> t_second = 
				std::make_tuple(s_pos, j, f_temp);
			f_temp--;
			mappedNotes.insert(std::make_pair(s.getNote(i), t_first));
			mappedNotes.insert(std::make_pair(s.getNote(i+1), t_second));
		}
	}
}

std::multimap<simplifiednote::SimplifiedNote, std::tuple<int, int, int>> NoteMapper::getMap() {
	return this->mappedNotes;
}


