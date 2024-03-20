#include "Instrument.h"

template<OutputViable OutputValue>
Instrument<OutputValue>::Instrument(std::vector<IString> sv) : strings(sv) {};

template<OutputViable OutputValue>
Instrument<OutputValue>::Instrument(std::initializer_list<IString> list) {
	for (IString s : list) {
		strings.push_back(s);	
	}
}

template<OutputViable OutputValue>
Instrument<OutputValue>::Instrument(std::vector<IString> sv, std::shared_ptr<ActionSet<OutputValue>> as) : action_set(as), strings(sv) {}

template<OutputViable OutputValue>
Instrument<OutputValue>::Instrument(std::shared_ptr<ActionSet<OutputValue>> as) : action_set(as) {}

template<OutputViable OutputValue>
Instrument<OutputValue>::~Instrument() {}

template<OutputViable OutputValue>
int Instrument<OutputValue>::makeIString(int pos, noteenums::Note start, noteenums::Note end) {
	if (pos < 1) {
		return -1;
	}
	for (auto s : strings) {
		if (s.getPosition() == pos) {
			return -1;
		} 
	}
	strings.push_back(IString(pos, start, end));
	return 1;
}

template<OutputViable OutputValue>
void Instrument<OutputValue>::addIString(IString s) {
	strings.push_back(s);
}

template<OutputViable OutputValue>
const std::shared_ptr<ActionSet<OutputValue>> Instrument<OutputValue>::getActionSet() const {
	return action_set;
}

template<OutputViable OutputValue>
const std::vector<IString>& Instrument<OutputValue>::getIStrings() {
	return strings;
}
