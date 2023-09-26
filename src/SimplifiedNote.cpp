#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"
#include "MXConverter.h"
#include <iostream>

using namespace noteenums;
using namespace simplifiednote;

//Throws exception if the convertion between mx and noteenums failed during construction.
SimplifiedNote::SimplifiedNote(mx::api::NoteData n) 
	try : note(MXConverter::ConvertNote(n)), 
	      duration(MXConverter::ConvertDuration(n)) {}
catch (ConversionException ce) {
	throw;	
}

Note SimplifiedNote::getNote() {
	return this->note;
}

Duration SimplifiedNote::getDuration() {
	return this->duration;
}

