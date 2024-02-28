#ifndef NOTE_MAPPER_H_MFPG
#define NOTE_MAPPER_H_MFPG

#include "IString.h"
#include "NoteEnums.h"
#include "PhysAttrMap.h"

#include <map>

//Virtual class for implementing a notemapper, InputTuple refers to the different
//ways a note can be played, this is what the concrete mapper is supposed to identify;
//all different ways a note can be played represented as InputTuple.
class NoteMapper {
	protected:
		virtual void mapString(const IString&) = 0;
                std::multimap<noteenums::Note, PhysAttrMap> mapped_notes;
        public:
	       	NoteMapper() {};
		virtual ~NoteMapper() {}
		const std::multimap<noteenums::Note, PhysAttrMap>& getMap() const {
			return mapped_notes;
		}
		int size() const {
			return mapped_notes.size();
		}
};
#endif
