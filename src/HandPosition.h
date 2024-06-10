#ifndef HAND_POSITION_H_MFPG
#define HAND_POSITION_H_MFPG

#include "SimplifiedNote.h"
#include "LayerList.h"

//A linked list 
template <class Output> class HandPosition {
	private:
		//Outgoing tuple state
		const PhysAttrMap state;
		//Represented note
		const SimplifiedNote note;
		//Points to the layerlist corresponding to this HandPosition
		const LayerList<Output>& layer_list; 
	public:
		HandPosition() = delete;
		HandPosition(PhysAttrMap, LayerList<Output>&);
		HandPosition(PhysAttrMap, SimplifiedNote, LayerList<Output>&);
		HandPosition(PhysAttrMap, SimplifiedNote, const LayerList<Output>&);
		
		const PhysAttrMap& getState() const;
		const SimplifiedNote& getNote() const;
		const LayerList<Output>& getLayerList() const;
}; 
#endif
