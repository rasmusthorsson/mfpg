#ifndef SOLVER_EXCEPTION_H_MFPG
#define SOLVER_EXCEPTION_H_MFPG

#include <exception>
#include <string>

class SolverException : public std::exception {

	private:
		const std::string errorMsg;
	public:
		SolverException(std::string);
		const std::string what(); 
};
#endif
