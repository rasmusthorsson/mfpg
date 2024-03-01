#include "Layer.h"

Layer::Layer() : note(Note::C_4, Duration::Whole) {};

Layer::Layer(noteenums::Note n, 
      noteenums::Duration d, 
      std::shared_ptr<NoteMapper> mapper) : note(n, d) {
	auto range = mapper->getMap().equal_range(n);
	for (auto i = range.first; i != range.second; ++i) {
		if (addNode(i->second) == -1) {
			throw(NodeException("Failed to add node to layer.\n", 
							i->second, note));
		}
	}		
}

Layer::Layer(noteenums::Note n, noteenums::Duration d) : note(n, d) {}

Layer::Layer(const SimplifiedNote& n, std::shared_ptr<NoteMapper> mapper) : note(n) {
	auto range = mapper->getMap().equal_range(note.getNote());
	for (auto i = range.first; i != range.second; ++i) {
		if (addNode(i->second) == -1) {
			throw(NodeException("Failed to add node to layer.\n", 
							i->second, note));
		}
	}
}

Layer::~Layer() {}

int Layer::addNode(const PhysAttrMap n) {
	const int old_size = nodes.size();
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (n == *i) {
			return -1;
		}
	}
	nodes.push_back(n);
	if (!(nodes.size() == old_size + 1)) {
		return -1;
	}
	return 1;
}

int Layer::removeNode(PhysAttrMap n) {
	if (nodes.size() < 1) {
		return -1;
	}
	for (auto i = nodes.begin(); i != nodes.end(); i++) {
		if (n == *i) {
			nodes.erase(i);
			return 1;
		}
	}
	return -1;
}

const PhysAttrMap& Layer::operator[](int index) const {
	if (index >= getSize()) {
		throw std::out_of_range("Layer index out of range.");
	}
	return nodes[index];
}

int Layer::getSize() const {
	return nodes.size();
}

void Layer::clear() {
	nodes.clear();
}

const SimplifiedNote& Layer::getNote() const {
	return note;
}

const std::vector<PhysAttrMap>& Layer::getNodes() const {
	return nodes;
}
