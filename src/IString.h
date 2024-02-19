#ifndef ISTRING_H_MFPG
#define ISTRING_H_MFPG

#include <vector>
#include "NoteEnums.h"
#include <iterator>
#include <cstddef>

//Class to represent Instrument Strings (The phyiscal strings of a string instrument).
class IString {
	private:
		const int position;
		const std::vector<noteenums::Note> playable_notes;
	public:
		IString(int, std::vector<noteenums::Note>);
		IString(int, int, int);
		IString(int, noteenums::Note, noteenums::Note);

		const int getPosition() const;
		const std::vector<noteenums::Note>& getPlayable() const;
		const noteenums::Note getNote(int) const;

		std::vector<noteenums::Note>::const_iterator end() const {
			return playable_notes.end();
		}
		std::vector<noteenums::Note>::const_iterator begin() const {
			return playable_notes.begin();
		}
};
#endif
