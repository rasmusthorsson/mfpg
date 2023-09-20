#include <exception>
#include "SimplifiedNote.h"

template <class T> class NodeException : public std::exception {
	private:
		const T* node;
		const simplifiednote::SimplifiedNote* note;
		const std::string errorMsg;
	public:
		NodeException(std::string msg, T* nd, simplifiednote::SimplifiedNote* nt);
		std::string what();
		T* failedNode();
		simplifiednote::SimplifiedNote* failedNote();
};
