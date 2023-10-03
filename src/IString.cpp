#include "IString.h"

IString::IString(int p, std::vector<noteenums::Note> n) : position(p), playableNotes(n) {}

IString::IString(int p, int range_start, int range_stop) : position(p), 
	playableNotes([range_start, range_stop]{
	std::vector<noteenums::Note> ret;
	for (int i = range_start; i <= range_stop; i++) {
		ret.push_back(static_cast<noteenums::Note>(i));
	}
	return ret;
	}())
{}

IString::IString(int p, noteenums::Note range_start, noteenums::Note range_stop) : position(p), 
	playableNotes([range_start, range_stop]{
	std::vector<noteenums::Note> ret;
	for (int i = static_cast<int>(range_start); i <= static_cast<int>(range_stop); i++) {
		ret.push_back(static_cast<noteenums::Note>(i));
	}
	return ret;
	}())
{}

int IString::getPosition() const {
	return this->position;
}

std::vector<noteenums::Note> IString::getPlayable() const {
	return this->playableNotes;
}

noteenums::Note IString::getNote(int i) const {
	return this->playableNotes[i];	
}

