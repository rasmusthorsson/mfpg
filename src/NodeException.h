#ifndef NOTE_EXCEPTION_H_MFPG
#define NOTE_EXCEPTION_H_MFPG

#include <exception>
#include "SimplifiedNote.h"

//Exception for attempting layer modification.
template <class T> class NodeException : public std::exception {
	private:
		const T node;
		const SimplifiedNote note;
		const std::string errorMsg;
	public:
		NodeException(std::string msg, T nd, SimplifiedNote nt) : 
			errorMsg(msg), node(nd), note(nt) {};
		const std::string what() {
			return errorMsg;
		};
		const T failedNode() const {
			return node;
		};
		const SimplifiedNote failedNote() const {
			return note;
		};
};
#endif
