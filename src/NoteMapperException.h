#include <exception>
#include <string>

class NoteMapperException : public std::exception {
	private:
		std::string err;
	public: 
		NoteMapperException(std::string);
		~NoteMapperException();
		std::string what();
};
