#ifndef LINK_EXCEPTION_H_MFPG
#define LINK_EXCEPTION_H_MFPG

#include <exception>
#include <string>

//Exception for attempting layerlist modification.
template <class Output> class LinkException : public std::exception {
	private:
		//Failure message
		const std::string errorMsg;
	public:
		LinkException(std::string); 
		const std::string what();
};
#endif
