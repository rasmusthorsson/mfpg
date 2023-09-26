#pragma once

#include <iostream>
#include "NoteEnums.h"
#include "mx/api/ScoreData.h"

using namespace noteenums;

namespace simplifiednote {

//Simpler way to represent notes compared to mx.
class SimplifiedNote {
	private:
		const Note note;
		const Duration duration;

	public:
		SimplifiedNote(mx::api::NoteData);
		Note getNote();
		Duration getDuration();
		bool operator < (const SimplifiedNote &rhs) const {
			return (static_cast<int>(note) < static_cast<int>(rhs.note));
		}
		bool operator > (const SimplifiedNote &rhs) const {
			return (static_cast<int>(note) > static_cast<int>(rhs.note));
		}
		friend inline std::ostream& operator<< (std::ostream& out, const SimplifiedNote n) {
			out << static_cast<int>(n.note);
			return out;	
		};
};

}
