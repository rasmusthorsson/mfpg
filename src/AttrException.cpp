#include "AttrException.h"

AttrException::AttrException(std::string s, std::vector<PhysTuple> a) : errorMsg(s), attr(a) {}

std::string AttrException::what() {
	return errorMsg;
}

const std::vector<PhysTuple>& AttrException::getAttr() const {
	return attr;
}
