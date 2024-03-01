#ifndef LAYER_H_MFPG
#define LAYER_H_MFPG

#include "SimplifiedNote.h"
#include "NodeException.h"
#include "NoteEnums.h"
#include "NoteMapper.h"
#include "PhysAttrMap.h"

#include <memory>
#include <vector>

//Class to represent a layer of nodes, each layer corresponds to a note in the music 
//piece, a node is generally a user-defined tuple, (simple example is a 3-tuple of 
//ints representing String, Hand Position, and Finger Position).
class Layer {
	private:
		const SimplifiedNote note;
		
		//All possible ways to play a the note (as represented by the tuple,
		//calculated by the notemapper.)
		std::vector<PhysAttrMap> nodes;
	public:
		Layer();
		Layer(noteenums::Note, noteenums::Duration, std::shared_ptr<NoteMapper>);
		Layer(noteenums::Note, noteenums::Duration);
		Layer(const SimplifiedNote&, std::shared_ptr<NoteMapper>);
		~Layer();

		//Attempts to add a node to a layer, if node is already present does 
		//nothing and returns -1.
		int addNode(const PhysAttrMap);
		//Attempts to remove a node from a layer, returns -1 if failure.
		int removeNode(PhysAttrMap);
		//Index the nodes
		
		const PhysAttrMap& operator[](int) const;
		int getSize() const;
		void clear();
		const SimplifiedNote& getNote() const;
		const std::vector<PhysAttrMap>& getNodes() const;	
};
#endif
