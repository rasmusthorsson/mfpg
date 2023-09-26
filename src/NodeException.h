#include <exception>
#include "SimplifiedNote.h"

//Exception for attempting layer modification.
template <class T> class NodeException : public std::exception {
	private:
		const T node;
		const simplifiednote::SimplifiedNote note;
		const std::string errorMsg;
	public:
		//Defined in header due to template issues with compiler.
		NodeException(std::string msg, T nd, simplifiednote::SimplifiedNote nt) : 
			errorMsg(msg), node(nd), note(nt) {};
		std::string what() {return errorMsg;};
		T failedNode() {return node;};
		simplifiednote::SimplifiedNote failedNote() {return note;};
};
