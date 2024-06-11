#include "ExValContainer.h"
#include "ExValException.h"

//--------------------------------- CONSTRUCTORS ---------------------------------
ExValContainer::ExValContainer(int i) : type('i'), ex_val(ExclusiveValue(i)) {}
ExValContainer::ExValContainer(double d) : type('d'), ex_val(ExclusiveValue(d)) {}
ExValContainer::ExValContainer(bool b) : type('b'), ex_val(ExclusiveValue(b)) {}

//--------------------------------- NESTED STRUCTS --------------------------------

ExValContainer::ExclusiveValue::ExclusiveValue(int _i) : i(_i) {}
ExValContainer::ExclusiveValue::ExclusiveValue(bool _b) : b(_b) {}
ExValContainer::ExclusiveValue::ExclusiveValue(double _d) : d(_d) {}
//--------------------------------- GETTERS ---------------------------------
const int ExValContainer::getI() const {
	if (type != 'i') {
		throw (ExValException("Exclusive Value is not an integer.\n", std::vector<ExValContainer>({*this})));
	}
	return ex_val.i;
}

const bool ExValContainer::getB() const {
	if (type != 'b') {
		throw (ExValException("Exclusive Value is not a boolean.\n", std::vector<ExValContainer>({*this})));
	}
	return ex_val.b;
}

const double ExValContainer::getD() const {
	if (type != 'd') {
		throw (ExValException("Exclusive Value is not a double.\n", std::vector<ExValContainer>({*this})));
	}
	return ex_val.d;
}

const char ExValContainer::getType() const {
	return type;
}

//--------------------------------- CONVERSIONS ---------------------------------
ExValContainer::operator int() {
	switch (type) {
		case 'i':
			return static_cast<int>(getI());
		case 'd':
			return static_cast<int>(getD());
		case 'b':
			return static_cast<int>(getB());
		default:
			return getI();
	}
}
ExValContainer::operator bool() {
	switch (type) {
		case 'i':
			return static_cast<bool>(getI());
		case 'd':
			return static_cast<bool>(getD());
		case 'b':
			return static_cast<bool>(getB());
		default:
			return getB();
	}
}
ExValContainer::operator double() {
	switch (type) {
		case 'i':
			return static_cast<double>(getI());
		case 'd':
			return static_cast<double>(getD());
		case 'b':
			return static_cast<double>(getB());
		default:
			return getD();
	}
}

//--------------------------------- STRINGS ---------------------------------
std::string ExValContainer::to_string() const {
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

std::string ExValContainer::to_string_csv() const {
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

std::ostream& operator << (std::ostream& out, ExValContainer tup) {
	out << tup.to_string();
	return out;
}

//------------------------------------------ OPERATORS -------------------------------------------------
//------------------------------------COMPARISON OPERATORS ---------------------------------------------

bool ExValContainer::operator == (const ExValContainer& rhs) const {
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
			throw (ExValException("Could not apply '==' operator, type unrecognized.", std::vector<ExValContainer>({*this, rhs})));
	}
}

bool ExValContainer::operator != (const ExValContainer& rhs) const {
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
			throw (ExValException("Could not apply '!=' operator, type unrecognized.", std::vector<ExValContainer>({*this, rhs})));
	}
}

bool operator > (const ExValContainer& lhs, const ExValContainer& rhs) {
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
			throw (ExValException("Could not apply '>' operator, type unrecognized.", std::vector<ExValContainer>({lhs, rhs})));
	}
}
bool operator < (const ExValContainer& lhs, const ExValContainer& rhs) {
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
			throw (ExValException("Could not apply '<' operator, type unrecognized.", std::vector<ExValContainer>({lhs, rhs})));
	}
}

//----------------------------------------- ARITHMETIC OPERATORS -----------------------------------

ExValContainer operator - (ExValContainer lhs, ExValContainer rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() == 'd') {
				return ExValContainer(lhs.getD() - rhs.getD());
			} else {
				throw ExValException("Attempting to apply 'minus' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		case 'i':
			if (rhs.getType() == 'i') {
				return ExValContainer(lhs.getI() - rhs.getI());
			} else {
				throw ExValException("Attempting to apply 'minus' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		case 'b':
			throw ExValException("Attempting to apply 'minus' operation to boolean.", std::vector<ExValContainer>({lhs, rhs}));
		default:
			throw ExValException("Type unrecognized for 'minus' operation.", std::vector<ExValContainer>({lhs, rhs}));
			
	}
}

ExValContainer operator + (ExValContainer lhs, ExValContainer rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() == 'd') {
				return ExValContainer(lhs.getD() + rhs.getD());
			} else {
				throw ExValException("Attempting to apply 'plus' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		case 'i':
			if (rhs.getType() == 'i') {
				return ExValContainer(lhs.getI() + rhs.getI());
			} else {
				throw ExValException("Attempting to apply 'plus' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		case 'b':
			throw ExValException("Attempting to apply 'plus' operation to boolean.", std::vector<ExValContainer>({lhs, rhs}));
		default:
			throw ExValException("Type unrecognized for 'plus' operation.", std::vector<ExValContainer>({lhs, rhs}));
	}
}

ExValContainer operator * (ExValContainer lhs, ExValContainer rhs) {
	switch (lhs.getType()) {
		case 'd':
			if (rhs.getType() == 'd') {
				return ExValContainer(lhs.getD() * rhs.getD());
			} else {
				throw ExValException("Attempting to apply 'multiplication' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		case 'i':
			if (rhs.getType() == 'i') {
				return ExValContainer(lhs.getI() * rhs.getI());
			} else {
				throw ExValException("Attempting to apply 'multiplication' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		case 'b':
			throw ExValException("Attempting to apply 'multiplication' operation to boolean.", std::vector<ExValContainer>({lhs, rhs}));
		default:
			throw ExValException("Type unrecognized for 'multiplication' operation.", std::vector<ExValContainer>({lhs, rhs}));
	}
}

//---------------------------------- BOOLEAN OPERATORS ------------------------------------------

ExValContainer operator && (ExValContainer lhs, ExValContainer rhs) {
	switch (lhs.getType()) {
		case 'd':
			throw ExValException("Attempting to apply 'conjunction' operation to double.", std::vector<ExValContainer>({lhs, rhs}));
		case 'i':
			throw ExValException("Attempting to apply 'conjunction' operation to int.", std::vector<ExValContainer>({lhs, rhs}));
		case 'b':
			if (rhs.getType() == 'b') {
				return ExValContainer(lhs.getB() && rhs.getB());
			} else {
				throw ExValException("Attempting to apply 'conjunction' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		default:
			throw ExValException("Type unrecognized for 'conjunction' operation.", std::vector<ExValContainer>({lhs, rhs}));
	}
}

ExValContainer operator || (ExValContainer lhs, ExValContainer rhs) {
	switch (lhs.getType()) {
		case 'd':
			throw ExValException("Attempting to apply 'disjunction' operation to double.", std::vector<ExValContainer>({lhs, rhs}));
		case 'i':
			throw ExValException("Attempting to apply 'disjunction' operation to int.", std::vector<ExValContainer>({lhs, rhs}));
		case 'b':
			if (rhs.getType() == 'b') {
				return ExValContainer(lhs.getB() || rhs.getB());
			} else {
				throw ExValException("Attempting to apply 'disjunction' operation to different types of Exclusive Value.", std::vector<ExValContainer>({lhs, rhs}));
			}
		default:
			throw ExValException("Type unrecognized for 'disjunction' operation.", std::vector<ExValContainer>({lhs, rhs}));
	}
}
