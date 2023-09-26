#include "ConversionException.h"

ConversionException::ConversionException(std::string message, mx::api::NoteData n) :
       	errorMsg(message),  
	note(n) {}

//Error message.
std::string ConversionException::what() {
	return this->errorMsg;
}

//What note caused the failure.
mx::api::NoteData ConversionException::failedNote() {
	return this->note;
}
