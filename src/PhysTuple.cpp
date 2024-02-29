#include "PhysTuple.h"
#include "AttrException.h"

PhysTuple::PhysTuple(int i) : type('i'), phys_attr(PhysAttr(i)) {}
PhysTuple::PhysTuple(double d) : type('d'), phys_attr(PhysAttr(d)) {}
PhysTuple::PhysTuple(bool b) : type('b'), phys_attr(PhysAttr(b)) {}

const int PhysTuple::getI() const {
	if (type != 'i') {
		throw (AttrException("Attribute is not an integer.\n", std::vector<PhysTuple>({*this})));
	}
	return phys_attr.i;
}

const bool PhysTuple::getB() const {
	if (type != 'b') {
		throw (AttrException("Attribute is not a boolean.\n", std::vector<PhysTuple>({*this})));
	}
	return phys_attr.b;
}

const double PhysTuple::getD() const {
	if (type != 'd') {
		throw (AttrException("Attribute is not a double.\n", std::vector<PhysTuple>({*this})));
	}
	return phys_attr.d;
}

const char PhysTuple::getType() const {
	return type;
}

PhysTuple::operator int() {
	return getI();
}
PhysTuple::operator bool() {
	return getB();
}
PhysTuple::operator double() {
	return getD();
}

std::string PhysTuple::to_string() const {
	std::string val;
	switch (type) {
		case 'i':
			val = std::to_string(getI());
			break;
		case 'd':
			val = std::to_string(getD());
			break;
		case 'b':
			if (getB()) {
				val = "true";
			} else {
				val = "false";
			}
			break;
		default:
			val = "NO_VAL";
	}
	return std::string("Type ") + type + ", Value: " + val;

}

std::string PhysTuple::to_string_csv() const {
	std::string val;
	switch (type) {
		case 'i':
			val = std::to_string(getI());
			break;
		case 'd':
			val = std::to_string(getD());
			break;
		case 'b':
			if (getB()) {
				val = "1";
			} else {
				val = "0";
			}
			break;
		default:
			val = "NO_VAL";
	}
	return val;

}

std::ostream& operator << (std::ostream& out, PhysTuple tup) {
	out << tup.to_string();
	return out;
}

//------------------------------------------ OPERATORS -------------------------------------------------
//------------------------------------COMPARISON OPERATORS ---------------------------------------------

bool PhysTuple::operator == (const PhysTuple& rhs) const {
	switch (getType()) {
		case 'i':
			if (rhs.getType() != 'i') {
				return false;
			} 
			return getI() == rhs.getI();
		case 'b':
			if (rhs.getType() != 'b') {
				return false;
			} 
			return getB() == rhs.getB();
		case 'd':
			if (rhs.getType() != 'd') {
				return false;
			} 
			return getD() == rhs.getD();
		default:
			throw (AttrException("Could not apply '==' operator, type unrecognized.", std::vector<PhysTuple>({*this, rhs})));
	}
}

bool PhysTuple::operator != (const PhysTuple& rhs) const {
	switch (getType()) {
		case 'i':
			if (rhs.getType() != 'i') {
				return true;
			} 
			return getI() != rhs.getI();
		case 'b':
			if (rhs.getType() != 'b') {
				return true;
			} 
			return getB() != rhs.getB();
		case 'd':
			if (rhs.getType() != 'd') {
				return true;
			} 
			return getD() != rhs.getD();
		default:
			throw (AttrException("Could not apply '!=' operator, type unrecognized.", std::vector<PhysTuple>({*this, rhs})));
	}
}

bool operator > (const PhysTuple& lhs, const PhysTuple& rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() != 'd') {
				return true;
			}
			return lhs.getD() > rhs.getD();
		case 'i':
			if (rhs.getType() == 'd') {
				return false;
			} else if (rhs.getType() == 'b') {
				return true;
			}
			return lhs.getI() > rhs.getI();
		case 'b':
			if (rhs.getType() != 'b') {
				return false;
			}
			return lhs.getB() > rhs.getB();
		default:
			throw (AttrException("Could not apply '>' operator, type unrecognized.", std::vector<PhysTuple>({lhs, rhs})));
	}
}
bool operator < (const PhysTuple& lhs, const PhysTuple& rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() != 'd') {
				return false;
			}
			return lhs.getD() < rhs.getD();
		case 'i':
			if (rhs.getType() == 'd') {
				return true;
			} else if (rhs.getType() == 'b') {
				return false;
			}
			return lhs.getI() < rhs.getI();
		case 'b':
			if (rhs.getType() != 'b') {
				return true;
			}
			return lhs.getB() < rhs.getB();
		default:
			throw (AttrException("Could not apply '<' operator, type unrecognized.", std::vector<PhysTuple>({lhs, rhs})));
	}
}

//----------------------------------------- ARITHMETIC OPERATORS -----------------------------------

PhysTuple operator - (PhysTuple lhs, PhysTuple rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() == 'd') {
				return PhysTuple(lhs.getD() - rhs.getD());
			} else {
				throw AttrException("Attempting to apply 'minus' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		case 'i':
			if (rhs.getType() == 'i') {
				return PhysTuple(lhs.getI() - rhs.getI());
			} else {
				throw AttrException("Attempting to apply 'minus' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		case 'b':
			throw AttrException("Attempting to apply 'minus' operation to boolean.", std::vector<PhysTuple>({lhs, rhs}));
		default:
			throw AttrException("Type unrecognized for 'minus' operation.", std::vector<PhysTuple>({lhs, rhs}));
			
	}
}

PhysTuple operator + (PhysTuple lhs, PhysTuple rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() == 'd') {
				return PhysTuple(lhs.getD() + rhs.getD());
			} else {
				throw AttrException("Attempting to apply 'plus' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		case 'i':
			if (rhs.getType() == 'i') {
				return PhysTuple(lhs.getI() + rhs.getI());
			} else {
				throw AttrException("Attempting to apply 'plus' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		case 'b':
			throw AttrException("Attempting to apply 'plus' operation to boolean.", std::vector<PhysTuple>({lhs, rhs}));
		default:
			throw AttrException("Type unrecognized for 'plus' operation.", std::vector<PhysTuple>({lhs, rhs}));
	}
}

PhysTuple operator * (PhysTuple lhs, PhysTuple rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() == 'd') {
				return PhysTuple(lhs.getD() * rhs.getD());
			} else {
				throw AttrException("Attempting to apply 'multiplication' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		case 'i':
			if (rhs.getType() == 'i') {
				return PhysTuple(lhs.getI() * rhs.getI());
			} else {
				throw AttrException("Attempting to apply 'multiplication' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		case 'b':
			throw AttrException("Attempting to apply 'multiplication' operation to boolean.", std::vector<PhysTuple>({lhs, rhs}));
		default:
			throw AttrException("Type unrecognized for 'multiplication' operation.", std::vector<PhysTuple>({lhs, rhs}));
	}
}

//---------------------------------- BOOLEAN OPERATORS ------------------------------------------

PhysTuple operator && (PhysTuple lhs, PhysTuple rhs) {
	switch (lhs.getType()) {
		case 'd':
			throw AttrException("Attempting to apply 'conjunction' operation to double.", std::vector<PhysTuple>({lhs, rhs}));
		case 'i':
			throw AttrException("Attempting to apply 'conjunction' operation to int.", std::vector<PhysTuple>({lhs, rhs}));
		case 'b':
			if (rhs.getType() == 'b') {
				return PhysTuple(lhs.getB() && rhs.getB());
			} else {
				throw AttrException("Attempting to apply 'conjunction' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		default:
			throw AttrException("Type unrecognized for 'conjunction' operation.", std::vector<PhysTuple>({lhs, rhs}));
	}
}

PhysTuple operator || (PhysTuple lhs, PhysTuple rhs) {
	switch (lhs.getType()) {
		case 'd':
			throw AttrException("Attempting to apply 'disjunction' operation to double.", std::vector<PhysTuple>({lhs, rhs}));
		case 'i':
			throw AttrException("Attempting to apply 'disjunction' operation to int.", std::vector<PhysTuple>({lhs, rhs}));
		case 'b':
			if (rhs.getType() == 'b') {
				return PhysTuple(lhs.getB() || rhs.getB());
			} else {
				throw AttrException("Attempting to apply 'disjunction' operation to different types of PhysAttr.", std::vector<PhysTuple>({lhs, rhs}));
			}
		default:
			throw AttrException("Type unrecognized for 'disjunction' operation.", std::vector<PhysTuple>({lhs, rhs}));
	}
}
