#include "Action.h"
#include <iterator>
#include <cstddef>

template <class InputTuple, class OutputValue> 
class ActionSet {
	private:
		std::vector<Action<InputTuple, OutputValue>> actions;
		//Perform each action in order, for each effective action, add that action to a
		//FIFO queue, for each new action check through entire queue and decide upon
		//whether action is modified/executed at all. This allows for combining actions
		//freely by user (if x action is taken, then skip y action for example). Actions
		//should be ordered in priority by user? do this here or elsewhere?
	public:
		ActionSet(std::vector<Action<InputTuple, OutputValue>> as) : actions(as) {}
		ActionSet(Action<InputTuple, OutputValue> a) {
			addAction(a);
		}
		ActionSet(std::initializer_list<Action<InputTuple, OutputValue>> as) {
			for (auto a : as) {
				actions.push_back(a);
			}
		}	

		void addAction(Action<InputTuple, OutputValue> a) {
			actions.push_back(a);
		}

		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = Action<InputTuple, OutputValue>;
			using pointer = Action<InputTuple, OutputValue>*;
			using reference = Action<InputTuple, OutputValue>&;
			private:
				pointer m_ptr;
			public:
				Iterator(pointer ptr) : m_ptr(ptr) {}
				reference operator*() const {return *m_ptr;}
				pointer operator->() {return m_ptr;}

				Iterator& operator++() {
					m_ptr++;
					return *this;
				}
				friend bool operator== (const Iterator& f, const Iterator& s)
						{ return f.m_ptr == s.m_ptr; }
				friend bool operator!= (const Iterator& f, const Iterator& s)
						{ return f.m_ptr != s.m_ptr; }
		};
		Iterator begin() {return Iterator(&actions[0]);}
		Iterator end() {return Iterator(&actions[actions.size()]);}
};
