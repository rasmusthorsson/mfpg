#include "SolverException.h"

SolverException::SolverException(std::string s) : errorMsg(s) {}

const std::string SolverException::what() {
	return errorMsg;
}
