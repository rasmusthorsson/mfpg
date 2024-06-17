#include "MXConverter.h"
#include "Log.h"
#include <set>
using namespace noteenums;
extern std::set<std::string> DEFINITIVES;

//Converts notes based on a regular 12-step chromatic scale, notes are converted to 
//their offset within an octave, the octave is then added as a multiple of 12, with 
//the alter added on the end. The alter is used for sharps or flats, but could also 
//be used to increase notes full steps if desired.
const Note MXConverter::ConvertNote(mx::api::NoteData& n) {
	DEFINITIVES.insert("NOTE");
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
	DEFINITIVES.insert("DURATION");
	switch(n.durationData.durationName) {
		case mx::api::DurationName::breve:
			return Duration::DoubleDur;
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
			mfpg_log::Log::verbose_out(std::cout,
				"No Duration Name was specified, defaulting to duration time tick...\n",
				mfpg_log::VERBOSE_LEVEL::VERBOSE_ALL
				);
			break;
	}
	int t = n.durationData.durationTimeTicks;
	if (t <= 3840 && t > 1920) {
		return Duration::DoubleDur;
	}
	else if (t <= 1920 && t > 960) {
		return Duration::Whole;
	}
	else if (t <= 960 && t > 480) {
		return Duration::Half;
	}
	else if (t <= 480 && t > 240) {
		return Duration::Quarter;
	}
	else if (t <= 240 && t > 120) {
		return Duration::Eighth;
	}
	else if (t <= 120 && t > 60) {
		return Duration::Sixteenth;
	}
	else if (t <= 60 && t > 30) {
		return Duration::ThirtySecond;
	}
	else if (t <= 30 && t > 15) {
		return Duration::SixtyFourth;
	}
	else {
		throw ConversionException("Duration not found.", n);
	}
}
