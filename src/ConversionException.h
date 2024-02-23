#ifndef CONVERSION_EXCEPTION_H_MFPG
#define CONVERSION_EXCEPTION_H_MFPG

#include "mx/api/ScoreData.h"

#include <exception>
#include <string>

//Exception for conversion failure between mx notes and noteenums notes.
class ConversionException : public std::exception {
	private:
		mx::api::NoteData& note;
		const std::string errorMsg;
	public:
		ConversionException(std::string, mx::api::NoteData&);
		std::string what();
		const mx::api::NoteData& failedNote() const;
};
#endif
