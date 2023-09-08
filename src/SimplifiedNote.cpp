#include "SimplifiedNote.h"
#include "mx/api/ScoreData.h"
#include "MXConverter.h"

using namespace noteenums;
using namespace simplifiednote;

SimplifiedNote::SimplifiedNote(mx::api::NoteData n) 
	try : note(MXConverter::ConvertNote(n)), 
	      acc(MXConverter::ConvertAcc(n)), 
	      duration(MXConverter::ConvertDuration(n)) {}
catch (ConversionException ce) {
	throw;	
}

SimplifiedNote::~SimplifiedNote() {

}

Note SimplifiedNote::getNote() {
	return this->note;
}

Accidental SimplifiedNote::getAcc() {
	return this->acc;
}

Duration SimplifiedNote::getDuration() {
	return this->duration;
}
