#ifndef LINK_EXCEPTION_H_MFPG
#define LINK_EXCEPTION_H_MFPG

#include <exception>

//Exception for attempting layerlist modification.
template <class Output> class LinkException : public std::exception {
	private:
		//Failure message
		const std::string errorMsg;
	public:
		LinkException(std::string s) : errorMsg(s) {}

		const std::string what() {
			return errorMsg;
		};
};
#endif
