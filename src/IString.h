#pragma once
#include <vector>
#include "NoteEnums.h"
#include <iterator>
#include <cstddef>

//Class to represent Instrument Strings (The phyiscal strings of a string instrument).
class IString {
	private:
		const int position;
		const std::vector<noteenums::Note> playableNotes;
	public:
		IString(int, std::vector<noteenums::Note>);
		IString(int, int, int);
		IString(int, noteenums::Note, noteenums::Note);
		int getPosition() const;
		std::vector<noteenums::Note> getPlayable() const;
		noteenums::Note getNote(int) const;

		std::vector<noteenums::Note>::const_iterator end() const 
			{return playableNotes.end();}
		std::vector<noteenums::Note>::const_iterator begin() const 
			{return playableNotes.begin();}
		std::vector<noteenums::Note>::const_iterator end() {
			return playableNotes.end();
		}
		std::vector<noteenums::Note>::const_iterator begin() {
			return playableNotes.begin();
		}
};
