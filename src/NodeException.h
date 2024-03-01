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
		NodeException(std::string, PhysAttrMap, SimplifiedNote); 

		const std::string what(); 
		const PhysAttrMap& failedNode() const;
		const SimplifiedNote& failedNote() const;
};
#endif
