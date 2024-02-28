#ifndef PHYS_ATTR_LIST_H_MFPG
#define PHYS_ATTR_LIST_H_MFPG

#include <initializer_list>
#include <map>
#include <string>
#include <vector>
#include <ostream>

#include "PhysTuple.h"

extern int TUPLESIZE;
extern char* ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

class PhysAttrMap {
	private: 
		std::map<const std::string, const PhysTuple> attr_map = {};
	public:
		PhysAttrMap() {};
		PhysAttrMap(std::vector<std::pair<const std::string, PhysTuple>> v);
		PhysAttrMap(std::initializer_list<std::pair<const std::string, PhysTuple>> list);
		PhysAttrMap(std::initializer_list<PhysTuple> list);
		const PhysTuple& getVal(std::string s) const; 
		bool operator == (const PhysAttrMap& rhs) const;
		bool operator != (const PhysAttrMap& rhs) const;
		std::string to_string() const;
		std::string to_string_csv() const;
		friend std::ostream& operator << (std::ostream& out, PhysAttrMap); 


		//Used of lexicographic sorting needed for map.
		struct AttrLess {
			bool operator() (const PhysAttrMap& lhs, const PhysAttrMap& rhs) const {
				bool acc = true;
				bool temp_acc = true;
				std::string key;

				for (int i = 0; i < ATTRIBUTES.size(); i++) {
					key = ATTRIBUTES[i];
					acc = lhs.attr_map.at(key) < rhs.attr_map.at(key);
					if (acc && temp_acc) {
						return true;
					}
					temp_acc &= lhs.attr_map.at(key) == rhs.attr_map.at(key); 
				}
				return false;
			}
		};
};
#endif
