#include "SimplifiedNote.h"
#include "NodeException.h"
#include <vector>

template<class T> class Layer {
	private:
		const simplifiednote::SimplifiedNote note;
		int size;
		std::vector<T> nodes;
	public:
		Layer(simplifiednote::SimplifiedNote);
		void addNode(T);
		void removeNode(T);
		std::vector<T> getNodes() {return nodes;};
};
