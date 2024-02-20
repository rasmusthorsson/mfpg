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
		//Map notes on an individual string,
		void mapString(IString& s);
	public:
		BasicNoteMapper() {}
		BasicNoteMapper(std::initializer_list<IString>);
		BasicNoteMapper(std::vector<IString>&);
		~BasicNoteMapper() {}
};
#endif
