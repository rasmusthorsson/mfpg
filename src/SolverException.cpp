#include "SolverException.h"

SolverException::SolverException(std::string s, int i) : errorMsg(s), layer(i) {}

const std::string SolverException::what() {
	return errorMsg;
}

int SolverException::getLayer() {
	return layer;
}
