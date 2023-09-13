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
	int notes = s.getPlayable().size();
	for (int i = 0; i < notes; i = i + 2) { //TODO possible off by one
		int f_temp = 4;
		if (i < 6) {
			f_temp = (i / 2) + 1;
		} else if (i > (notes - 7)) {
			f_temp = ((notes - i) / 2) + 1;
		}
		for (int j = ((i + 1) / 2) + 1; j < ((i + 1) / 2) + f_temp + 1; j++) {
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

std::map<simplifiednote::SimplifiedNote, std::tuple<int, int, int>> NoteMapper::getMap() {
	return this->mappedNotes;
}
