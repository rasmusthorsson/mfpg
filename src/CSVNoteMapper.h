#ifndef CSV_NOTEMAPPER_MFPG_H
#define CSV_NOTEMAPPER_MFPG_H

#include "NoteMapper.h"

class CSVNoteMapper : public NoteMapper {
	private:
		std::multimap<noteenums::Note, PhysAttrMap> full_map;
	protected:
		void mapString(const IString&);
	public:
		CSVNoteMapper(std::string, const std::vector<IString>&);
		~CSVNoteMapper();

};

#endif
