#include <exception>
#include <string>
#include "mx/api/ScoreData.h"

//Exception for conversion failure between mx notes and noteenums notes.
class ConversionException : public std::exception {
	private:
		mx::api::NoteData note;
		std::string errorMsg;
	public:
		ConversionException(std::string message, mx::api::NoteData);
		std::string what();
		mx::api::NoteData failedNote();
};
