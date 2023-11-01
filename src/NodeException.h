#include <exception>
#include "SimplifiedNote.h"

//Exception for attempting layer modification.
template <class T> class NodeException : public std::exception {
	private:
		const T node;
		const SimplifiedNote note;
		const std::string errorMsg;
	public:
		//Defined in header due to template issues with compiler.
		NodeException(std::string msg, T nd, SimplifiedNote nt) : 
			errorMsg(msg), node(nd), note(nt) {};
		std::string what() {return errorMsg;};
		T failedNode() {return node;};
		SimplifiedNote failedNote() {return note;};
};
