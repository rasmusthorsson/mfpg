#ifndef EX_VAL_EXCEPTION_MFPG_H
#define EX_VAL_EXCEPTION_MFPG_H

#include <exception>
#include <string>
#include <vector>

#include "ExValContainer.h"

class ExValException : public std::exception {
	private:
		std::string errorMsg;
		const std::vector<ExValContainer> ex_val;
	public:
		ExValException(std::string s, std::vector<ExValContainer> a);
		std::string what();
		const std::vector<ExValContainer>& getExVal() const;
};

#endif
