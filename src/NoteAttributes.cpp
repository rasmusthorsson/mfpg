#include "NoteAttributes.h"

NoteAttributes::NoteAttributes(const PhysAttrMap& p, const SimplifiedNote& n) 
	: phys_attr(p), note(n.getNote()), duration(n.getDuration()) {}

NoteAttributes::NoteAttributes(const PhysAttrMap& p) : phys_attr(p), 
	note(noteenums::Note::C_4), duration(noteenums::Duration::Quarter) {

}

const PhysAttrMap& NoteAttributes::getPhysAttr() {
	return phys_attr;
}

const noteenums::Note& NoteAttributes::getNote() {
	return note;
}

const noteenums::Duration& NoteAttributes::getDuration() {
	return duration;
}
