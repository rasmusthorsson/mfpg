#include <map>
#include <tuple>
#include <vector>
#include "NoteMapper.h"

//Basic implementation of NoteMapper as an example, converts notes into 3-tuples of String,
//Hand Position, and Finger Position combinations.
class BasicNoteMapper : public virtual NoteMapper<std::tuple<int, int, int>>{
	private:
		void mapString(IString s);
	public:
		BasicNoteMapper(std::vector<IString> strings);
		std::multimap<noteenums::Note, std::tuple<int, int, int>> getMap() const;
};
