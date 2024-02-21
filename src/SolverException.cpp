#include "SolverException.h"

SolverException::SolverException(std::string s, int i) : errorMsg(s), count(i) {}

const std::string SolverException::what() {
	return errorMsg;
}

int SolverException::getCount() {
	return count;
}
