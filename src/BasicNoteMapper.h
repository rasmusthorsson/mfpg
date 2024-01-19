#ifndef BASIC_NOTE_MAPPER_H_MFPG
#define BASIC_NOTE_MAPPER_H_MFPG

#include <map>
#include <tuple>
#include <vector>
#include "NoteMapper.h"

//Basic implementation of NoteMapper as an example, converts notes into 3-tuples of 
//String, Hand Position, and Finger Position combinations.
class BasicNoteMapper : public virtual NoteMapper<std::tuple<int, int, int>>{
	private:
		void mapString(IString s);
	public:
		//Maps all strings in a vector, if the input is all available IStrings
		//then all playable notes are mapped.
		BasicNoteMapper(std::vector<IString>);
};
#endif
