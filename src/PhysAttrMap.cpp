#include "PhysAttrMap.h"
#include "AttrException.h"

#include <ostream>
#include <typeinfo>

extern int TUPLESIZE;
extern char* ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

PhysAttrMap::PhysAttrMap(std::initializer_list<std::pair<const std::string, PhysTuple>> list) {
	if (list.size() != TUPLESIZE) {
		std::vector<PhysTuple> ex_v;
		for (auto pair : list) {
			ex_v.push_back(pair.second);
		}
		std::cout << "TUPLE SIZE: " << TUPLESIZE << "\n";
		throw (AttrException("List size is not the same as TUPLESIZE.", ex_v));
	}
	int count = 0;
	for (auto pair : list) {
		if (ATTRIBUTE_TYPES[count] != pair.second.getType()) {
			throw (AttrException("Attribute map is not consistent with attribute types.", std::vector<PhysTuple>({pair.second})));
		}
		count++;
		attr_map.insert(pair);
	}
}
PhysAttrMap::PhysAttrMap(std::initializer_list<PhysTuple> list) {
	if (list.size() != TUPLESIZE) {
		std::vector<PhysTuple> ex_v;
		for (auto p : list) {
			ex_v.push_back(p);
		}
		throw (AttrException("List size is not the same as TUPLESIZE.", ex_v));
	}
	int ind = 0;
	for (auto l : list) {
		if (l.getType() != ATTRIBUTE_TYPES[ind]) {
			throw (AttrException("Attribute map is not consistent with attribute types.", std::vector<PhysTuple>({list})));
		}
		attr_map.insert({ATTRIBUTES[ind], l});
		ind++;
	}
}
const PhysTuple& PhysAttrMap::getVal(std::string s) const {
	return attr_map.at(s);
}

bool PhysAttrMap::operator == (const PhysAttrMap& rhs) const {
	auto this_itr = attr_map.cbegin();
	auto other_itr = rhs.attr_map.cbegin();
	
	for (int i = 0; i < attr_map.size(); i++) {
		if (this_itr->first != other_itr->first) {
			return false;
		}
		if (this_itr->second != other_itr->second) {
			return false;
		}
		this_itr++;
		other_itr++;
	}
	return true;
}

bool PhysAttrMap::operator != (const PhysAttrMap& rhs) const {
	return !(*this == rhs);
}


std::string PhysAttrMap::to_string() const {
	std::string ret = "";
	if (attr_map.size() < 1) {
		return "Empty";
	}
	for (const std::string attr : ATTRIBUTES) {
		ret += "Name: " + attr + " PhysTuple: " + attr_map.at(attr).to_string() + "\n";
	}
	return ret;
}

std::string PhysAttrMap::to_string_csv() const {
	std::string ret = "";
	if (attr_map.size() < 1) {
		return "Empty";
	}
	for (const std::string attr : ATTRIBUTES) {
		ret += attr_map.at(attr).to_string_csv() + ",";
	}
	return ret;
}

std::ostream& operator << (std::ostream& out, PhysAttrMap map) {
	out << map.to_string();
	return out;
}
