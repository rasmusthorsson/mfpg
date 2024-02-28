#ifndef INSTTRUMENT_H_MFPG
#define INSTTRUMENT_H_MFPG

#include "ActionSet.h"
#include "NoteEnums.h"
#include "IString.h"

#include <memory>
#include <vector>
#include <string>

template <OutputViable Cost> class Instrument {
	private:
		std::vector<IString> strings;
		const std::shared_ptr<ActionSet<Cost>> action_set;
	public:
		Instrument() {};
		Instrument(std::vector<IString> sv) : strings(sv) {};
		Instrument(std::vector<IString> sv, std::shared_ptr<ActionSet<Cost>> as) 
			   	: action_set(as), strings(sv) {}
		Instrument(std::shared_ptr<ActionSet<Cost>> as) : action_set(as) {}
		~Instrument() {}

		//Builds a string and adds it to the vector, returns -1 if the string position is occupied.
		int makeIString(int pos, noteenums::Note start, noteenums::Note end) {
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

		void setActionSet(std::shared_ptr<ActionSet<Cost>> as) {
			action_set = new ActionSet<Cost>(*as);
		}
		const std::shared_ptr<ActionSet<Cost>> getActionSet() const {
			return action_set;
		}
		const std::vector<IString>& getIStrings() {
			return strings;
		}
};
#endif
