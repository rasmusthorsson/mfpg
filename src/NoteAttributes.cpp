#include "NoteAttributes.h"

NoteAttributes::NoteAttributes(const PhysAttrMap& p, const SimplifiedNote& n) : phys_attr(p), note(n) {}

const PhysAttrMap& NoteAttributes::getPhysAttr() {
	return phys_attr;
}

const noteenums::Note& NoteAttributes::getNote() {
	return note.getNote();
}

const noteenums::Duration& NoteAttributes::getDuration() {
	return note.getDuration();
}
