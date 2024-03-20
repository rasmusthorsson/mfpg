#include "PhysAttrMap.h"
#include "ExValException.h"

#include <ostream>

//----------------------------------------- GLOBALS -----------------------------------------
extern int TUPLESIZE;
extern std::string ATTRIBUTE_TYPES;
extern std::vector<std::string> ATTRIBUTES;

//----------------------------------------- CONSTRUCTORS -----------------------------------------
PhysAttrMap::PhysAttrMap(std::initializer_list<std::pair<const std::string, ExValContainer>> list) {
	if (list.size() != TUPLESIZE) {
		std::vector<ExValContainer> ex_v;
		for (auto pair : list) {
			ex_v.push_back(pair.second);
		}
		throw (ExValException("List size is not the same as TUPLESIZE.", ex_v));
	}
	for (auto pair : list) {
		int attr_index = 0;
		for (; attr_index < ATTRIBUTES.size(); attr_index++) {
			if (ATTRIBUTES[attr_index] == pair.first) {
				break;
			}
		}
		if (ATTRIBUTE_TYPES[attr_index] != pair.second.getType()) {
			throw (ExValException("Attribute map is not consistent with attribute types.", std::vector<ExValContainer>({pair.second})));
		}
		auto inserted_val = attr_map.insert(pair);
		if (!inserted_val.second) {
			throw (ExValException("Attribute map already contains a value of this attribute type.", std::vector<ExValContainer>({pair.second})));
		}
	}
}
PhysAttrMap::PhysAttrMap(std::initializer_list<ExValContainer> list) {
	if (list.size() != TUPLESIZE) {
		std::vector<ExValContainer> ex_v;
		for (auto p : list) {
			ex_v.push_back(p);
		}
		throw (ExValException("List size is not the same as TUPLESIZE.", ex_v));
	}
	int ind = 0;
	for (auto l : list) {
		if (l.getType() != ATTRIBUTE_TYPES[ind]) {
			throw (ExValException("Attribute map is not consistent with attribute types.", std::vector<ExValContainer>({list})));
		}
		attr_map.insert({ATTRIBUTES[ind], l});
		ind++;
	}
}

//----------------------------------------- NESTED STRUCT ---------------------------------------
bool PhysAttrMap::AttrLess::operator() (const PhysAttrMap& lhs, const PhysAttrMap& rhs) const {
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

//----------------------------------------- GETTERS -----------------------------------------
const ExValContainer& PhysAttrMap::getVal(std::string s) const {
	return attr_map.at(s);
}
const ExValContainer& PhysAttrMap::getVal(int i) const {
	return attr_map.at(ATTRIBUTES[i]);
}

//----------------------------------------- OPERATORS -----------------------------------------
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

//----------------------------------------- STRINGS -----------------------------------------
std::string PhysAttrMap::to_string() const {
	std::string ret = "";
	if (attr_map.size() < 1) {
		return "Empty";
	}
	for (const std::string attr : ATTRIBUTES) {
		ret += "Name: " + attr + " ExValContainer: " + attr_map.at(attr).to_string() + "\n";
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
