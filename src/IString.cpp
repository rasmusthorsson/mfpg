#include "IString.h"

IString::IString(int p, std::vector<simplifiednote::SimplifiedNote> n) : position(p), playableNotes(n) {}

int IString::getPosition() {
	return this->position;
}

std::vector<simplifiednote::SimplifiedNote> IString::getPlayable() {
	return this->playableNotes;
}

simplifiednote::SimplifiedNote IString::getNote(int i) {
	return this->playableNotes[i];	
}

