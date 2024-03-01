#include "NodeException.h"

NodeException::NodeException(std::string msg, PhysAttrMap nd, SimplifiedNote nt) : errorMsg(msg), node(nd), note(nt) {}

const std::string NodeException::what() {
	return errorMsg;
}
const PhysAttrMap& NodeException::failedNode() const {
	return node;
}
const SimplifiedNote& NodeException::failedNote() const {
	return note;
}
