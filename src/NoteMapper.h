#include "IString.h"
#include "NoteEnums.h"
#include <map>

//Virtual class for implementing a notemapper, class T refers to tuple representing the
//way notes are to be presented to the path algorithm.
template <class T> class NoteMapper {
	protected:
                std::multimap<noteenums::Note, T> mappedNotes;
        public:
	       	NoteMapper() {};
		virtual std::multimap<noteenums::Note, T> getMap() const = 0;

};
