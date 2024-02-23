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
		virtual void mapString(const IString&) = 0;
                std::multimap<noteenums::Note, InputTuple> mapped_notes;
        public:
	       	NoteMapper() {};
		virtual ~NoteMapper() {}
		const std::multimap<noteenums::Note, InputTuple>& getMap() const {
			return mapped_notes;
		}
		int size() const {
			return mapped_notes.size();
		}
};
#endif
