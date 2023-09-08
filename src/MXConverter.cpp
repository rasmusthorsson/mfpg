#include "MXConverter.h"

using namespace noteenums;

Note MXConverter::ConvertNote(mx::api::NoteData n) {
	switch(n.pitchData.step) {
		case mx::api::Step::a:
			return Note::A;
		case mx::api::Step::b:
			return Note::B;
		case mx::api::Step::c:
			return Note::C;
		case mx::api::Step::d:
			return Note::D;
		case mx::api::Step::e:
			return Note::E;
		case mx::api::Step::f:
			return Note::F;
		case mx::api::Step::g:
			return Note::G;
		default:
			throw ConversionException("Note not found.", n); 
	}
}

Accidental MXConverter::ConvertAcc(mx::api::NoteData n) {
	switch(n.pitchData.accidental) {
		case mx::api::Accidental::sharp:
			return Accidental::Sharp;
		case mx::api::Accidental::flat:
			return Accidental::Flat;
		case mx::api::Accidental::natural:
			return Accidental::Natural;
		default:
			return Accidental::None;
	}
}

Duration MXConverter::ConvertDuration(mx::api::NoteData n) {
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
