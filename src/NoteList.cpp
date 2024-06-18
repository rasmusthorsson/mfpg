#include "NoteList.h"

using namespace std;
using namespace mx::api;
using it = std::list<SimplifiedNote>::const_iterator;

extern std::string INSTRUMENT_NAME;

NoteList::NoteList() : notes() {};

NoteList::NoteList(const ScoreData& score) {
	loadNotes(score);
}

const void NoteList::loadNotes(const ScoreData& score) {
	for (PartData p: score.parts) {
		if (p.name == INSTRUMENT_NAME) {
			for (MeasureData m: p.measures) {
				for (StaffData s: m.staves) {
					for (NoteData n: s.voices.at(0).notes) {
						notes.push_back(n);
					}
				}
			}
			return;
		}
	}
	throw std::out_of_range("Could not find an instrument by the name:" + INSTRUMENT_NAME + "\n");
}

int NoteList::size() const {
	return notes.size();
}

const SimplifiedNote& NoteList::front() const {
	return notes.front();
}

const list<SimplifiedNote>& NoteList::getNotes() const {
	return notes;
}
