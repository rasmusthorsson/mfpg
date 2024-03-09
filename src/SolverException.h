#ifndef SOLVER_EXCEPTION_H_MFPG
#define SOLVER_EXCEPTION_H_MFPG

#include "SimplifiedNote.h"

#include <exception>
#include <string>

class SolverException : public std::exception {

	private:
		const std::string errorMsg;
		//Count refers to the layer that was reached before the exception was thrown.
		int count;
	public:
		SolverException(std::string, int);
		const std::string what();
		int getCount();
};
#endif
