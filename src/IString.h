#pragma once
#include <vector>
#include "NoteEnums.h"

//Class to represent Instrument Strings (The phyiscal strings of a string instrument).
class IString {
	private:
		const int position;
		const std::vector<noteenums::Note> playableNotes;
	public:
		IString(int p, std::vector<noteenums::Note> n);
		int getPosition();
		std::vector<noteenums::Note> getPlayable();
		noteenums::Note getNote(int i);
};
