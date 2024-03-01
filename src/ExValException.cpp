#include "ExValException.h"

ExValException::ExValException(std::string s, std::vector<ExValContainer> a) : errorMsg(s), ex_val(a) {}

std::string ExValException::what() {
	return errorMsg;
}

const std::vector<ExValContainer>& ExValException::getExVal() const {
	return ex_val;
}
