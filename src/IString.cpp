#include "IString.h"

using namespace std;

//Vector init
IString::IString(int p, vector<noteenums::Note> n) : position(p), playableNotes(n)
{}

//Range init 0 to HIGHEST_NOTE (72)
IString::IString(int p, int rangeStart, int rangeStop) : position(p), 
	playableNotes([rangeStart, rangeStop]{
	vector<noteenums::Note> ret;
	for (int i = rangeStart; i <= rangeStop; i++) {
		ret.push_back(static_cast<noteenums::Note>(i));
	}
	return ret;
	}())
	{}

//Note init using note names
IString::IString(int p, noteenums::Note range_start, noteenums::Note range_stop) 
									: position(p), 
	playableNotes([range_start, range_stop]{
	vector<noteenums::Note> ret;
	for (int i = static_cast<int>(range_start); i <= static_cast<int>(range_stop); 
									i++) {
		ret.push_back(static_cast<noteenums::Note>(i));
	}
	return ret;
	}())
	{}

int IString::getPosition() const {
	return this->position;
}

vector<noteenums::Note> IString::getPlayable() const {
	return this->playableNotes;
}

noteenums::Note IString::getNote(int i) const {
	return this->playableNotes[i];	
}

