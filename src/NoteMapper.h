#ifndef NOTE_MAPPER_H_MFPG
#define NOTE_MAPPER_H_MFPG

#include "IString.h"
#include "NoteEnums.h"
#include <map>
#include <utility>

//Virtual class for implementing a notemapper, InputTuple refers to the different
//ways a note can be played, this is what the concrete mapper is supposed to identify;
//all different ways a note can be played represented as InputTuple.
template <class InputTuple> class NoteMapper {
		using it = std::multimap<noteenums::Note, InputTuple>::iterator;
	protected:
		//Define how notes are mapped in child.
		virtual void mapString(IString) = 0;
                std::multimap<noteenums::Note, InputTuple> mappedNotes;
        public:
	       	NoteMapper() {};
		
		std::multimap<noteenums::Note, InputTuple> getMap() {
			return mappedNotes;
		}
		int size() {
			return mappedNotes.size();
		}

		//TODO define iterator instead?
		std::pair<it, it> getRange(noteenums::Note n) {
			return mappedNotes.equal_range(n);
		}
		it getUpper(noteenums::Note n) {
			return mappedNotes.upper_bound(n);
		}
		it getLower(noteenums::Note n) {
			return mappedNotes.lower_bound(n);
		}
		it begin() {
			return mappedNotes.begin();
		}
		it end() {
			return mappedNotes.end();
		}		
};
#endif
