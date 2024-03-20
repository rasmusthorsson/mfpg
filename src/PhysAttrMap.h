#ifndef PHYS_ATTR_LIST_H_MFPG
#define PHYS_ATTR_LIST_H_MFPG

#include <initializer_list>
#include <map>
#include <string>
#include <ostream>

#include "ExValContainer.h"

class PhysAttrMap {
	private: 
		//Map to index via string rather than template index as with tuples.
		std::map<const std::string, const ExValContainer> attr_map = {};
	public:
		PhysAttrMap() {};
		
		//Constructor where you specify attribute names along with their values as a pair, must
		//contain TUPLESIZE amount of attributes, must not contain duplicates. 
		PhysAttrMap(std::initializer_list<std::pair<const std::string, ExValContainer>> list);
		PhysAttrMap(std::initializer_list<ExValContainer> list);

		//Returns the ExValContainer of the corresponding mapped value of the string input.
		const ExValContainer& getVal(std::string) const; 
		const ExValContainer& getVal(int) const; 

		bool operator == (const PhysAttrMap&) const;
		bool operator != (const PhysAttrMap&) const;
		std::string to_string() const;
		std::string to_string_csv() const;
		friend std::ostream& operator << (std::ostream&, PhysAttrMap); 

		//lexicographic sorting needed for comparisons when inserting into map in LayerList.
		struct AttrLess {
			bool operator() (const PhysAttrMap&, const PhysAttrMap&) const;
		};
};
#endif
