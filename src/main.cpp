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
#include "Instrument.h"

#include <iostream>
#include <string>
#include <cstdint>
#include <sstream>
#include <fstream>

using namespace noteenums;
using namespace std;

int main (int argc, char *argv[]) {

//-------------------------------- Input/Arguments -------------------------
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

//------------------------- MX conversion --------------------------------

	using namespace mx::api;

	auto& mgr = DocumentManager::getInstance();

	istringstream istr{sheet_music};
	const auto documentID = mgr.createFromStream(istr);
	const auto score = mgr.getData(documentID);
	mgr.destroyDocument(documentID);
	NoteList noteList(score);

//---------------------- Instrument creation ----------------------------

	using Real_Rep_Tuple = std::tuple<int, int, int>;
	using Cost = int;
	
	typedef std::tuple<bool, Cost> (*action_type) (Real_Rep_Tuple, Real_Rep_Tuple);

	IString G_s(1, Note::G_3, Note::Gs_5);
	IString D_s(2, Note::D_4, Note::Ds_6);
	IString A_s(3, Note::A_4, Note::As_6);
	IString E_s(4, Note::E_4, Note::F_6);
	
	std::vector<IString> strings{G_s, D_s, A_s, E_s};

	NoteMapper<Real_Rep_Tuple>* note_mapper = new BasicNoteMapper(strings);

	action_type HP_action = [] (Real_Rep_Tuple t1, Real_Rep_Tuple t2) {
		int out = std::abs(std::get<1>(t1) - std::get<1>(t2));
		return std::tuple<bool, Cost>{true, out};
	};
	action_type finger_action = [] (Real_Rep_Tuple t1, Real_Rep_Tuple t2) {
		int out = std::abs(std::get<2>(t1) - std::get<2>(t2));
		return std::tuple<bool, Cost>{true, out};
	};
	action_type string_action_no_rest = [] (Real_Rep_Tuple t1, Real_Rep_Tuple t2) {
		int out = 0;
		if (std::abs(std::get<0>(t1) - std::get<0>(t2)) >= 2) {
			out = out + 100;
		} else {
			out = out + std::abs(std::get<0>(t1) - std::get<0>(t2));
		}
		return std::tuple<bool, Cost>{true, out};
	};
	action_type string_action_rest = [] (Real_Rep_Tuple t1, Real_Rep_Tuple t2) {
		int out = std::abs(std::get<0>(t1) - std::get<0>(t2));
		return std::tuple<bool, Cost>{true, out};
	};
	action_type rest = [] (Real_Rep_Tuple t1, Real_Rep_Tuple t2) {
		if (t1 == Real_Rep_Tuple{0, 0, 0} || t2 == Real_Rep_Tuple{0, 0, 0}) {
			return std::tuple<bool, Cost>{true, 0};
		}
		return std::tuple<bool, Cost>{false, 0};
	};

	Action<Real_Rep_Tuple, Cost> r(rest, "rest"); 
	Action<Real_Rep_Tuple, Cost> s_a_NR(string_action_no_rest, 
							"string_action_no_rest");
	Action<Real_Rep_Tuple, Cost> s_a_R(string_action_rest, "string_action_rest");
	Action<Real_Rep_Tuple, Cost> f_a(finger_action, "finger_action");
	Action<Real_Rep_Tuple, Cost> hp_a(HP_action, "hand_position_action");
	ActionSet<Real_Rep_Tuple, Cost> action_set({
						{r, true},
						{s_a_NR, true},
						{s_a_R, false}, 
						{f_a, true}, 
						{hp_a, true}
						});
	action_set.addDependency("string_action_no_rest", "rest", false);
	action_set.addDependency("string_action_rest", "rest", true);
	
	Instrument<Real_Rep_Tuple, Cost> violin(strings, note_mapper, action_set);

//-------------------------- Graph building/solving -------------------------

	LayerList<Real_Rep_Tuple, Cost> list(noteList, violin.getNoteMapper());	
	list.buildTransitions(violin.getActionSet());
	
	GraphSolver<Real_Rep_Tuple, Cost>* solver = new GreedySolver();
	solver->solve(list);

//------------------------------ Output ----------------------------------

	int count = 1;
	//TODO Fix ties
	for (auto sol : solver->getSolution()) {
		std::cout << "Note number: " << count << "\n";
		std::cout << "Note: " << std::get<0>(sol).getNote() << "\n";
		std::cout << "String: " << std::get<0>(std::get<0>(sol).getState())
		          << ", Finger: " << std::get<2>(std::get<0>(sol).getState()) 
			  << ", Hand Position: " 
			  << std::get<1>(std::get<0>(sol).getState()) << "\n"
			  << "Cost of transition: " << std::get<1>(sol) << "\n"
			  << "------------------------------------" << "\n";
		count++;
	}
	return 1;

}
