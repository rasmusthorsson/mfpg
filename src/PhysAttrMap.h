#ifndef PHYS_ATTR_LIST_H_MFPG
#define PHYS_ATTR_LIST_H_MFPG

#include <map>
#include <string>
#include <vector>

const int TUPLESIZE = 3;
const char* ATTRIBUTES = "iid";
//Possible physical attribute types
class PhysTuple {
	private:
		union PhysAttr {
			public:
				explicit PhysAttr(int _i) : i(_i) {};
				explicit PhysAttr(bool _b) : b(_b) {};
				explicit PhysAttr(double _d) : d(_d) {};
				PhysAttr() = delete;
				int i;
				bool b;
				double d;
		};
		const PhysAttr phys_attr;
		const char type;
	public:
		PhysTuple() = delete;
		explicit PhysTuple(int i) : type('i'), phys_attr(PhysAttr(i)) {}
		explicit PhysTuple(double d) : type('d'), phys_attr(PhysAttr(d)) {}
		explicit PhysTuple(bool b) : type('b'), phys_attr(PhysAttr(b)) {}
		const int getI() const {
			if (type != 'i') {
				//throw exception
			}
			return phys_attr.i;
		}
		const bool getB() const {
			if (type != 'b') {
				//throw exception
			}
			return phys_attr.b;
		}
		const double getD() const {
			if (type != 'd') {
				//throw exception
			}
			return phys_attr.d;
		}
		const char getType() const {
			return type;
		}
};

class PhysAttrMap {
	private: 
		std::map<const std::string, const PhysTuple> attr_map = {};
	public:
		PhysAttrMap(std::vector<std::pair<const std::string, PhysTuple>> v){
			if (v.size() != TUPLESIZE) {
				//TODO throw exception
			}
			for (int i = 0; i < TUPLESIZE; i++) {
				if (ATTRIBUTES[i] != v[i].second.getType()) {
					//throw exception
				}
				attr_map.insert(v[i]);
			}
			
		}
		const PhysTuple& getVal(std::string s) {
			return attr_map.at(s);
		}

};
#endif
