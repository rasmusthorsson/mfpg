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
                std::multimap<noteenums::Note, InputTuple> mapped_notes;
        public:
	       	NoteMapper() {};
		virtual ~NoteMapper() {}	
		std::multimap<noteenums::Note, InputTuple> getMap() {
			return mapped_notes;
		}
		int size() {
			return mapped_notes.size();
		}

		//TODO define iterator instead?
		std::pair<it, it> getRange(noteenums::Note n) {
			return mapped_notes.equal_range(n);
		}
		it getUpper(noteenums::Note n) {
			return mapped_notes.upper_bound(n);
		}
		it getLower(noteenums::Note n) {
			return mapped_notes.lower_bound(n);
		}
		it begin() {
			return mapped_notes.begin();
		}
		it end() {
			return mapped_notes.end();
		}		
};
#endif
