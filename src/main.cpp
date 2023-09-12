#include "mx/api/ScoreData.h"
#include "mx/api/DocumentManager.h"
#include "NoteList.h"

#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>

using namespace std;

int main (int argc, char *argv[]) {
	if (argc < 2) {
		cout << "Please specify an input MusicXML file.\n";
		return -1;
	} else if (argc > 2) {
		cout << "Too many arguments.\n";
		return -1;
	}
	ifstream input_file;
	input_file.open(argv[1]);
	if (!input_file.is_open()) {
		cout << "Could not open file: " << argv[1] << "\n";
		return -1;
	}
	string buffer;
	string sheet_music;
	while (input_file) {
		getline(input_file, buffer);
		sheet_music = sheet_music + "\n" + buffer;
	}

	using namespace mx::api;

	auto& mgr = DocumentManager::getInstance();

	istringstream istr{sheet_music};
	const auto documentID = mgr.createFromStream(istr);
	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	NoteList n(score);
	
	return 1;

}
