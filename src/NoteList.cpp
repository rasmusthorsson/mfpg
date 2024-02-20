#include "NoteList.h"

using namespace std;
using namespace mx::api;
using it = std::list<SimplifiedNote>::const_iterator;

NoteList::NoteList(const ScoreData& score) : notes(loadNotes(score)) {}

const std::list<SimplifiedNote> NoteList::loadNotes(const ScoreData& score) {
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

const SimplifiedNote& NoteList::front() const {
	return notes.front();
}

const list<SimplifiedNote>& NoteList::getNotes() const {
	return notes;
}

const it NoteList::begin() const {
	return notes.begin();
}

const it NoteList::end() const {
	return notes.end();
}
