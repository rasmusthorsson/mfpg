#include "NoteMapperException.h"

NoteMapperException::NoteMapperException(std::string s) : err(s) {}

NoteMapperException::~NoteMapperException() {}

std::string NoteMapperException::what() {
	return err;
}
