#ifndef ISTRING_H_MFPG
#define ISTRING_H_MFPG

#include "NoteEnums.h"

#include <vector>

//Class to represent Instrument Strings (The phyiscal strings of a string instrument).
class IString {
	private:
		//String position relative to other strings
		const int position;
		//Notes which can be played on the string
		const std::vector<noteenums::Note> playable_notes;
	public:
		//Init by vector
		IString(int, std::vector<noteenums::Note>);
		//Init by int range
		IString(int, int, int);
		//Init by note range
		IString(int, noteenums::Note, noteenums::Note);

		const int getPosition() const;

		const std::vector<noteenums::Note>& getPlayable() const;
		
		const noteenums::Note getNote(int) const;
};
#endif
