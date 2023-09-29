#pragma once
#include <exception>
#include "LayerList.h"

template <class T, class C> class LayerListException : std::exception {
	private:
		const std::string errorMsg;
		LayerList<T, C> link;
		const bool forward;
	public:
		LayerListException(const std::string m, const bool b, LayerList<T, C> l) 
			: errorMsg(m), forward(b), link(l) {}
		const std::string what() {
			return errorMsg;
		}
		LayerList<T, C> failedLink() {
			return link;
		}
		const bool isForward() {
			return forward;
		}
};
