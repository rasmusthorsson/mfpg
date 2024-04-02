#ifndef CSV_NOTEMAPPER_MFPG_H
#define CSV_NOTEMAPPER_MFPG_H

#include "NoteMapper.h"

class CSVNoteMapper : public NoteMapper {
	protected:
		std::multimap<noteenums::Note, PhysAttrMap> full_map;
		void mapString(const IString&);
	public:
		CSVNoteMapper(std::string, const std::vector<IString>&);
		~CSVNoteMapper();

};

#endif
