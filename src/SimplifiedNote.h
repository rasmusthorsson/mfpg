#ifndef SIMPLIFIED_NOTE_H_MFPG
#define SIMPLIFIED_NOTE_H_MFPG

#include <string>
#include <iostream>
#include "NoteEnums.h"
#include "mx/api/ScoreData.h"

using namespace noteenums;

//Simpler way to represent notes compared to mx. Used to make it easier to make 
//additions in the future.
class SimplifiedNote {
	private:
		const Note note;
		const Duration duration;
	public:
		SimplifiedNote() : note(Note::C_4), duration(Duration::Whole) {}
		SimplifiedNote(mx::api::NoteData);
		SimplifiedNote(Note n, Duration d);

		Note getNote();
		Duration getDuration();

		bool operator < (const SimplifiedNote &rhs) const {
			return (static_cast<int>(note) < static_cast<int>(rhs.note));
		}
		bool operator > (const SimplifiedNote &rhs) const {
			return (static_cast<int>(note) > static_cast<int>(rhs.note));
		}
		friend inline std::ostream& operator<< (std::ostream& out, 
							const SimplifiedNote n) {
			out << n.note;
			return out;	
		};
};
#endif
