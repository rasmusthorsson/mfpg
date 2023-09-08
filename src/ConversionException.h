#include <exception>
#include <string>
#include "mx/api/ScoreData.h"

class ConversionException : public std::exception {
	private:
		mx::api::NoteData note;
		std::string errorMsg;
	public:
		ConversionException(std::string message, mx::api::NoteData);
		std::string err();
		mx::api::NoteData failedNote();
};
