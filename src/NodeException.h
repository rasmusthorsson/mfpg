#ifndef NODE_EXCEPTION_H_MFPG
#define NODE_EXCEPTION_H_MFPG

#include "SimplifiedNote.h"
#include "PhysAttrMap.h"

#include <exception>
#include <string>

//Exception for attempting layer modification.
class NodeException : public std::exception {
	private:
		//Node which failed.
		const PhysAttrMap node;

		//Note represented by the node.
		const SimplifiedNote note;

		//Failure message
		const std::string errorMsg;
	public:
		NodeException(std::string msg, PhysAttrMap nd, SimplifiedNote nt) 
						: errorMsg(msg), node(nd), note(nt) {};
		const std::string what() {
			return errorMsg;
		};
		const PhysAttrMap& failedNode() const {
			return node;
		};
		const SimplifiedNote& failedNote() const {
			return note;
		};
};
#endif
