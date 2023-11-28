#include "ConversionException.h"

ConversionException::ConversionException(std::string message, mx::api::NoteData n) :
       	errorMsg(message),  
	note(n) {}

//Error message.
const std::string ConversionException::what() {
	return errorMsg;
}

//What note caused the failure.
mx::api::NoteData ConversionException::failedNote() const {
	return note;
}
