#include <fstream>
#include <string>

#include "Builder.h"


int main(int argc, char* argv[]) {
	using namespace noteenums;
	
	std::string out_file;

	if (argc < 2) {
		std::cout << "No output detected, defaulting to CSV_Map.csv.\n";
		out_file = "CSV_Map.csv";
	} else if (argc > 2) {
		std::cout << "Too many arguments, this program only takes an output file name as argument.\n";
		return -1;
	} else {
		out_file = std::string(argv[1]);
	}

	//Open filename out_file as output.
	std::ofstream f;
	f.open(out_file);
	
	//The first CSV column must be the note.
	std::string s = "Note,";

	//Specify which notes should be considered, this is usually all of them here, but then a tighter
	//restriction is given in the NoteMapper proper.
	Builder b(Note::C_0, Note::B_8);
	s += b.build();
	f << s;
	return 1;
}

