#include "IString.h"
#include "NoteEnums.h"
#include <map>

class NoteMapper {
	protected:
                std::multimap<noteenums::Note, std::tuple<int, int, int>> mappedNotes;
        public:
	       	NoteMapper() {};
		virtual std::multimap<noteenums::Note, std::tuple<int, int, int>> getMap() = 0;

};
