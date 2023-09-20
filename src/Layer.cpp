#include "Layer.h"
#include <cassert>

template<class T> Layer<T>::Layer(simplifiednote::SimplifiedNote n) : note(n) {}

template<class T> void Layer<T>::addNode(T n) {
	int old_size = nodes.size();
	assert(old_size == size);
	nodes.push_back(n);
	if (nodes.size() == old_size + 1) {
		this.size += 1;
	} else {
		assert(nodes.size() == size);
		throw NodeException("Could not add node to note layer.", *n, note);
	}
}

template<class T> void Layer<T>::removeNode(T n) {
	int v_size = nodes.size();
	assert(v_size == size);
	if (size < 1) {
		throw NodeException("Can not remove node from note layer, note layer is empty.",
				*n, note);
	}
	for (T nd : nodes) {
		if (n == nd) {
			nodes.erase(nd);
			size -= 1;
			return;
		}
	}
	throw NodeException("Could not locate node in note layer.", *n, note);
}
