#include "ConversionException.h"

ConversionException::ConversionException(std::string message, mx::api::NoteData n) :
       	errorMsg(message),  
	note(n) {}

std::string ConversionException::what() {
	return this->errorMsg;
}

mx::api::NoteData ConversionException::failedNote() {
	return this->note;
}
