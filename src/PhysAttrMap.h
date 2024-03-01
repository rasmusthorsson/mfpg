#ifndef PHYS_ATTR_LIST_H_MFPG
#define PHYS_ATTR_LIST_H_MFPG

#include <initializer_list>
#include <map>
#include <string>
#include <vector>
#include <ostream>

#include "ExValContainer.h"

//Global variables to ensure correct behaviour and defining allowed actions.
extern int TUPLESIZE;
extern char* ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

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
		const ExValContainer& getVal(std::string s) const; 

		bool operator == (const PhysAttrMap& rhs) const;
		bool operator != (const PhysAttrMap& rhs) const;
		std::string to_string() const;
		std::string to_string_csv() const;
		friend std::ostream& operator << (std::ostream& out, PhysAttrMap); 

		//lexicographic sorting needed for comparisons when inserting into map in LayerList.
		struct AttrLess {
			bool operator() (const PhysAttrMap& lhs, const PhysAttrMap& rhs) const;
		};
};
#endif
