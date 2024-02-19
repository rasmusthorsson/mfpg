#include "IString.h"

using namespace std;

//Vector init
IString::IString(int p, vector<noteenums::Note> n) : position(p), playable_notes(n)
{}

//Range init 0 to HIGHEST_NOTE (72)
IString::IString(int p, int range_start, int range_stop) : position(p), 
	playable_notes([range_start, range_stop]{
	vector<noteenums::Note> ret;
	for (int i = range_start; i <= range_stop; i++) {
		ret.push_back(static_cast<noteenums::Note>(i));
	}
	return ret;
	}())
	{}

//Note init using note names
IString::IString(int p, noteenums::Note range_start, noteenums::Note range_stop) 
									: position(p), 
	playable_notes([range_start, range_stop]{
	vector<noteenums::Note> ret;
	for (int i = static_cast<int>(range_start); i <= static_cast<int>(range_stop); 
									i++) {
		ret.push_back(static_cast<noteenums::Note>(i));
	}
	return ret;
	}())
	{}

const int IString::getPosition() const {
	return this->position;
}

const vector<noteenums::Note>& IString::getPlayable() const {
	return this->playable_notes;
}

const noteenums::Note IString::getNote(int i) const {
	return this->playable_notes[i];	
}

