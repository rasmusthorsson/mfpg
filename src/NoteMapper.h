#include <map>
#include <tuple>
#include <vector>
#include "IString.h"

class NoteMapper{
	private:
		//Maps all notes to a 3-tuple of String, Hand Position and Finger, 
		//currently done according to static rules.
		//
		//TODO Consider modifying to allow for dynamic number of tuples with
		//rules defined by the user instead.
		std::map<simplifiednote::SimplifiedNote, std::tuple<int, int, int>> mappedNotes;
		void mapString(IString s);
	public:
		NoteMapper(std::vector<IString> strings);
		std::map<simplifiednote::SimplifiedNote, std::tuple<int, int, int>> getMap();
};
