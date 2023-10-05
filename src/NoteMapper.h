#include "IString.h"
#include "NoteEnums.h"
#include <map>
#include <utility>

//Virtual class for implementing a notemapper, class T refers to tuple representing the
//way notes are to be presented to the path algorithm.
template <class T> class NoteMapper {
		using it = std::multimap<noteenums::Note, T>::iterator;
	protected:
		//Define how notes are mapped in child.
		virtual void mapString(IString) = 0;
                std::multimap<noteenums::Note, T> mappedNotes;
        public:
	       	NoteMapper() {};

		//TODO define iterator instead?
		std::pair<it, it> getRange(noteenums::Note n) {return mappedNotes.equal_range(n);}
		it getUpper(noteenums::Note n) {return mappedNotes.upper_bound(n);}
		it getLower(noteenums::Note n) {return mappedNotes.lower_bound(n);}
		it begin() {return mappedNotes.begin();}
		it end() {return mappedNotes.end();}
		std::multimap<noteenums::Note, T> getMap() {return mappedNotes;}
		int size() {return mappedNotes.size();}
		
};
