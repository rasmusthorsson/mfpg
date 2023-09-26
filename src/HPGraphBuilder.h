#include "Action.h"
#include <list>
#include <map>
#include "Layer.h"

template <class T, class C> class HPGraphBuilder : public std::list<Layer<T>> {
	private:
		//Map each tuple in the current layer to an array of values, each value at position
		//n in the array corresponds to the cost of transitioning from the mapped tuple
		//to the n'th tuple in the next layer.
		std::map<T, std::vector<C>> transitions;
		std::vector<Action<T, C>> actionSet;
	public:
		HPGraphBuilder() {
			auto t = this.begin();
			for (T tuple : t) {
				for (T tuple : std::next(t, 1)) {
					//TODO: Find a different approach?
				}
			}
		};

};	
