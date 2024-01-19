#include "mx/api/ScoreData.h"
#include "mx/api/DocumentManager.h"

#include "NoteEnums.h"
#include "IString.h"
#include "BasicNoteMapper.h"
#include "Action.h"
#include "ActionSet.h"
#include "LayerList.h"
#include "NoteList.h"
#include "NoteMapper.h"
#include "GraphSolver.h"
#include "GreedySolver.h"

#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>

using namespace noteenums;
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
	NoteList noteList(score);
	
	using in_type = std::tuple<int, int, int>;
	using out_type = int;
	
	typedef out_type (*action_type) (in_type, in_type);

	IString s1(1, Note::Gs_3, Note::Gs_5);
	IString s2(2, Note::Ds_4, Note::Ds_6);
	IString s3(3, Note::As_4, Note::As_6);
	IString s4(4, Note::F_4, Note::F_6);
		
	std::vector<IString> sv{s1, s2, s3, s4};
	NoteMapper<in_type>* mapper = new BasicNoteMapper(sv);

	action_type action1 = [] (in_type t1, in_type t2) {
		int out = std::abs(std::get<1>(t1) - std::get<1>(t2));
		out = out + std::abs(std::get<2>(t1) - std::get<2>(t2));
		if (std::abs(std::get<0>(t1) - std::get<0>(t2)) >= 2) {
			out = out + 100;
		} else {
			out = out + 1;
		}
		return out;
	};

	Action<in_type, out_type> a1(action1, "A1");
	ActionSet<in_type, out_type> action_set({a1, true});

	LayerList<in_type, out_type> list(noteList, mapper);	
	list.buildTransitions(action_set);
	
	GraphSolver<in_type, out_type>* solver = new GreedySolver();
	solver->solve(list);
	int count = 1;
	
	//TODO Fix breaks and ties, fix input in AW
	for (auto sol : solver->getSolution()) {
		std::cout << "Note number: " << count << "\n";
		std::cout << "Note: " << std::get<0>(sol).getNote() << "\n";
		std::cout << "String: " << std::get<0>(std::get<0>(sol).getState())
		          << ", Finger: " << std::get<2>(std::get<0>(sol).getState()) 
			  << ", Hand Position: " << 
			  	std::get<1>(std::get<0>(sol).getState()) << "\n" 
			  << "------------------------------------" << "\n";
		count++;
	}
	//given an instrument and a notelist, construct a valid and optimal position 
	//graph corresponding to the notelist.

	return 1;

}
