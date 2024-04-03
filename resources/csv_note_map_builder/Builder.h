#include <string>

#include "../../src/NoteEnums.h"

//Uncomment the below comment if you have defined your own notemapper.
//#define CUSTOM

#ifdef CUSTOM
#define build_file_CUSTOM build
#else
#define build_file build
#endif

class Builder {
	private:
		//Notes to be considered
		std::vector<noteenums::Note> notes;

		//Helper for building individual rows
		std::string build_row(noteenums::Note, std::initializer_list<std::string>);
	public:
		//Defines a range of notes to be considered.
		Builder(noteenums::Note, noteenums::Note);
		~Builder();
		
		//Builds the main string to be in the file.
		std::string build_file();

		//Custom notebuilder for users to build.
		std::string build_file_CUSTOM();
		
};
