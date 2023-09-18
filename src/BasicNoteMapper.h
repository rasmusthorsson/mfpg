#include <map>
#include <tuple>
#include <vector>
#include "NoteMapper.h"

class BasicNoteMapper : public virtual NoteMapper{
	private:
		void mapString(IString s);
	public:
		BasicNoteMapper(std::vector<IString> strings);
		std::multimap<noteenums::Note, std::tuple<int, int, int>> getMap();
};
