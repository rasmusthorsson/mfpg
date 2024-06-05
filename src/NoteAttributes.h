#ifndef NOTE_ATTRIBUTES_H_MFPG
#define NOTE_ATTRIBUTES_H_MFPG
#include "PhysAttrMap.h"
#include "NoteEnums.h"
#include "SimplifiedNote.h"

class NoteAttributes {
	private:	
		const PhysAttrMap& phys_attr;
		const noteenums::Note note;
		const noteenums::Duration duration;
	public:
		NoteAttributes() = delete; 
		NoteAttributes(const PhysAttrMap&);
		NoteAttributes(const PhysAttrMap&, const SimplifiedNote&); 
		const PhysAttrMap& getPhysAttr();
		const noteenums::Note& getNote();
		const noteenums::Duration& getDuration();
};
#endif
