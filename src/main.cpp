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

	cout << n.size() << ".\n";	
	
	return 1;

}
/*
int main (int argc, char *argv[]) {
	ifstream myfile;
	string temp;
	string mystring;
	myfile.open("../resources/test.txt");
	while (myfile) {
		getline(myfile, temp);
		mystring = mystring + "\n" + temp; 
	}
	using namespace mx::api;
	auto& mgr = DocumentManager::getInstance();
	istringstream istr{mystring};
	const auto documentID = mgr.createFromStream(istr);
	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	if (score.parts.size() != 1)
	{
		return 1;
	}
	const auto& part = score.parts.at(0);
	const auto& measure = part.measures.at(0);
	const auto& staff = measure.staves.at(0);
	const auto& voice = staff.voices.at(0);
	const auto& note = voice.notes.at(0);
	SimplifiedNote note1(note);
	std::cout << typeid(voice).name() << endl;
	std::cout << typeid(note).name() << endl;
	if (note.durationData.durationName != DurationName::whole)
	{
		return 1;
	}
	if (note.pitchData.step != Step::c) 
	{
		return 1;
	}
	return 1;
}
*/
