#include <iostream>

#include "SimplifiedNote.h"
#include "MXConverter.h"

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

const Note& SimplifiedNote::getNote() const {
	return note;
}

const Duration& SimplifiedNote::getDuration() const {
	return duration;
}

