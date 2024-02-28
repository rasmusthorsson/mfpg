#ifndef ATTR_EXCEPTION_MFPG_H
#define ATTR_EXCEPTION_MFPG_H

#include <exception>
#include <string>
#include <vector>

#include "PhysTuple.h"

class AttrException : public std::exception {
	private:
		std::string errorMsg;
		const std::vector<PhysTuple> attr;
	public:
		AttrException(std::string s, std::vector<PhysTuple> a);
		std::string what();
		const std::vector<PhysTuple>& getAttr() const;
};

#endif
