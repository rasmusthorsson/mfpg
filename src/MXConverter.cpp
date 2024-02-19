#include "MXConverter.h"

using namespace noteenums;

//Converts notes based on a regular 12-step chromatic scale, notes are converted to 
//their offset within an octave, the octave is then added as a multiple of 12, with 
//the alter added on the end. The alter is used for sharps or flats, but could also 
//be used to increase notes full steps if desired.
const Note MXConverter::ConvertNote(mx::api::NoteData& n) {
	if (n.isRest) {
		return Note::REST;
	} 
	int base;
	switch(n.pitchData.step) {
		case mx::api::Step::a:
			base = 9;
			break;
		case mx::api::Step::b:
			base = 11;
			break;
		case mx::api::Step::c:
			base = 0;
			break;
		case mx::api::Step::d:
			base = 2;
			break;
		case mx::api::Step::e:
			base = 4;
			break;
		case mx::api::Step::f:
			base = 5;
			break;
		case mx::api::Step::g:
			base = 7;
			break;
		default:
			throw ConversionException("Note not found.", n); 
	}
	int simp_note = base + n.pitchData.octave * 12 + n.pitchData.alter;
	if (simp_note > HIGHEST_NOTE || simp_note < 0) {
		throw ConversionException("Note out of range.", n); 
	}
	return static_cast<Note>(simp_note);
}

//Basic conversion between mx durations to noteenum durations.
const Duration MXConverter::ConvertDuration(mx::api::NoteData& n) {
	switch(n.durationData.durationName) {
		case mx::api::DurationName::breve:
			return Duration::Double;
		case mx::api::DurationName::whole:
			return Duration::Whole;
		case mx::api::DurationName::half:
			return Duration::Half;
		case mx::api::DurationName::quarter:
			return Duration::Quarter;
		case mx::api::DurationName::eighth:
			return Duration::Eighth;
		case mx::api::DurationName::dur16th:
			return Duration::Sixteenth;
		case mx::api::DurationName::dur32nd:
			return Duration::ThirtySecond;
		case mx::api::DurationName::dur64th:
			return Duration::SixtyFourth;
		default:
			throw ConversionException("Duration not found.", n); 
	}
}
