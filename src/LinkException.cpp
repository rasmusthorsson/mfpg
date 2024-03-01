#include "LinkException.h"

template<typename OutputValue>
LinkException<OutputValue>::LinkException(std::string s) : errorMsg(s) {}

template<typename OutputValue>
const std::string LinkException<OutputValue>::what() {
	return errorMsg;
}
