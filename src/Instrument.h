#ifndef INSTTRUMENT_H_MFPG
#define INSTTRUMENT_H_MFPG

#include "ActionSet.h"
#include "NoteEnums.h"
#include "IString.h"

#include <memory>
#include <vector>
#include <string>

template <OutputViable OutputValue> class Instrument {
	private:
		std::vector<IString> strings;
		const std::shared_ptr<ActionSet<OutputValue>> action_set;
	public:
		Instrument() {};
		Instrument(std::initializer_list<IString>);
		Instrument(std::vector<IString>);
		Instrument(std::vector<IString>, std::shared_ptr<ActionSet<OutputValue>>);
		Instrument(std::shared_ptr<ActionSet<OutputValue>>);
		~Instrument();

		void addIString(IString);
		//Builds a string and adds it to the vector, returns -1 if the string position is occupied.
		int makeIString(int pos, noteenums::Note, noteenums::Note);
		const std::shared_ptr<ActionSet<OutputValue>> getActionSet() const;
		const std::vector<IString>& getIStrings();
};
#endif
