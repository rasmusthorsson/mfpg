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
					notes.push_back(n);
				}
			}
		}
	}	
}

int NoteList::size() {
	return notes.size();
}

SimplifiedNote NoteList::front() {
	return notes.front();
}

void NoteList::popFront() {
	notes.pop_front();
}

list<SimplifiedNote> NoteList::getNotes() {
	return notes;
}
