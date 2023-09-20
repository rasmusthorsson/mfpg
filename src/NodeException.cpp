#include "NodeException.h"

template<class T> NodeException<T>::NodeException(std::string err, T* nd, 
		simplifiednote::SimplifiedNote* nt) : errorMsg(err), node(nd), note(nt) {}

template<class T> std::string NodeException<T>::what() {
	return errorMsg;
}

template<class T> T* NodeException<T>::failedNode() {
	return node;
}

template<class T> simplifiednote::SimplifiedNote* NodeException<T>::failedNote() {
	return note;
}
