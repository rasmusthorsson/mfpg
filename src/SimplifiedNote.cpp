#include "SimplifiedNote.h"
#include "MXConverter.h"
#include <iostream>

using namespace noteenums;

//Throws exception if the convertion between mx and noteenums failed during 
//construction.
SimplifiedNote::SimplifiedNote(mx::api::NoteData n) 
	try : note(MXConverter::ConvertNote(n)), 
	      duration(MXConverter::ConvertDuration(n)) {}
	catch (ConversionException ce) {
		throw;	
}

SimplifiedNote::SimplifiedNote(Note n, Duration d): note(n), duration(d) {}

Note SimplifiedNote::getNote() {
	return this->note;
}

Duration SimplifiedNote::getDuration() {
	return this->duration;
}

