#include "Action.h"
#include <iterator>
#include <cstddef>
#include <map>

//Probably move this to Action.h?
template<typename T>
concept Measurable = requires(T a, T b) {
	a + b; //Placeholder
	//TODO define concept for measurablility for output
};

template <class InputTuple, class OutputValue> 
class ActionSet {
	private:
		std::vector<std::tuple<Action<InputTuple, OutputValue>, bool>> actions;
		std::multimap<std::string, std::tuple<std::string, bool>> eventmap;
	public:
		ActionSet() {};
		ActionSet(std::vector<std::tuple<Action<InputTuple, OutputValue>, 
				bool>> as) : actions(as) {}
		ActionSet(Action<InputTuple, OutputValue> a, bool b) {
			addAction(a, b);
		}
		ActionSet(std::initializer_list
				<std::tuple<Action<InputTuple, OutputValue>, bool>> as) {
			for (auto a : as) {
				actions.push_back(a);
			}
		}	

		void addAction(Action<InputTuple, OutputValue> a, bool b) {
			std::tuple<Action<InputTuple, OutputValue>, bool> t(a, b);
			actions.push_back(t);
		}
		
		OutputValue apply(InputTuple n1, InputTuple n2) {
			OutputValue output = 0; //Acceptable if Measurable is defined
						//with convertability in mind
			std::vector<std::string> taken = {};
			for (auto a : actions) {
				//output = output + a.distance(n1, n2);

			}
			return output;	
		}

		//Iterator not necessary?
		struct Iterator {
			using it_cat = std::forward_iterator_tag;
			using diff_t = std::ptrdiff_t;
			using val_t = std::tuple<Action<InputTuple, OutputValue>, bool>;
			using pointer = val_t*;
			using reference = val_t&;
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
				Iterator operator++(int) {
					pointer prev = m_ptr;
					m_ptr++;
					return Iterator(prev);
				}
				friend bool operator== (const Iterator& f, const Iterator& s)
						{ return f.m_ptr == s.m_ptr; }
				friend bool operator!= (const Iterator& f, const Iterator& s)
						{ return f.m_ptr != s.m_ptr; }
		};
		Iterator begin() {return Iterator(&actions[0]);}
		Iterator end() {return Iterator(&actions[actions.size()]);}
};
