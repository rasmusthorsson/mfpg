#include "NoteList.h"

using namespace std;
using namespace mx::api;

NoteList::NoteList(ScoreData score) {
	loadNotes(score);	
}

//Loads notes into list, implicit conversion to simplifiednote.
void NoteList::loadNotes(ScoreData score) {
	for (PartData p: score.parts) {
		for (MeasureData m: p.measures) {
			for (StaffData s: m.staves) {
				for (NoteData n: s.voices.at(0).notes) {
					list::push_back(n);
				}
			}
		}
	}	
}

