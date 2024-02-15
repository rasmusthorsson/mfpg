#include "NoteList.h"

using namespace std;
using namespace mx::api;
using it = std::list<SimplifiedNote>::const_iterator;

NoteList::NoteList(ScoreData score) : notes(loadNotes(score)) {}

//Loads notes into list, implicit conversion to simplifiednote.
const std::list<SimplifiedNote> NoteList::loadNotes(ScoreData score) {
	std::list<SimplifiedNote> ret;
	for (PartData p: score.parts) {
		for (MeasureData m: p.measures) {
			for (StaffData s: m.staves) {
				for (NoteData n: s.voices.at(0).notes) {
					ret.push_back(n);
				}
			}
		}
	}
	return ret;
}

int NoteList::size() const {
	return notes.size();
}

const SimplifiedNote NoteList::front() const {
	return notes.front();
}

const list<SimplifiedNote> NoteList::getNotes() const {
	return notes;
}

it NoteList::begin() const {
	return notes.begin();
}
