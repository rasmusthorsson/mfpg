#ifndef PHYS_TUPLE_H_MFPG
#define PHYS_TUPLE_H_MFPG

#include <ostream>
#include <iostream>

//Class for dealing with physical attributes without relying on templates.
class PhysTuple {
	private:
		//Storage for possible fundamental types supported.
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
		const char type; //Character representing which type is stored using typeid values.
	public:
		//Constructors are the only way to set the values.
		PhysTuple() = delete;
		PhysTuple(int i);
		PhysTuple(double d);
		PhysTuple(bool b);

		//Getters for supported fundamental types, throws an exception if the getter used does not
		//correspond with the type that is stored.
		const int getI() const;
		const bool getB() const;
		const double getD() const;
		
		const char getType() const;
		std::string to_string() const; //String in readable format
		std::string to_string_csv() const; //CSV format following the ATTRIBUTES

		//Conversions to fundamentals.
		operator int();
		operator bool();
		operator double();

		friend PhysTuple operator - (const PhysTuple lhs, const PhysTuple rhs);
		friend PhysTuple operator + (const PhysTuple lhs, const PhysTuple rhs);
		friend PhysTuple operator * (const PhysTuple lhs, const PhysTuple rhs);
		friend PhysTuple operator && (const PhysTuple lhs, const PhysTuple rhs);
		friend PhysTuple operator || (const PhysTuple lhs, const PhysTuple rhs);

		bool operator == (const PhysTuple& rhs) const;
		bool operator != (const PhysTuple& rhs) const;
		friend bool operator > (const PhysTuple& lhs, const PhysTuple& rhs);
		friend bool operator < (const PhysTuple& lhs, const PhysTuple& rhs);
		
		//Outputs the "to_string" string.
		friend std::ostream& operator << (std::ostream& out, PhysTuple tup);
};

#endif
