#ifndef PHYS_TUPLE_H_MFPG
#define PHYS_TUPLE_H_MFPG

#include <ostream>
#include <iostream>

class PhysTuple {
	private:
		union PhysAttr {
			public:
				PhysAttr(int _i) : i(_i) {};
				PhysAttr(bool _b) : b(_b) {};
				PhysAttr(double _d) : d(_d) {};
				PhysAttr() = delete;
				int i;
				bool b;
				double d;
		};
		const PhysAttr phys_attr;
		const char type;
	public:
		PhysTuple() = delete;
		PhysTuple(int i);
		PhysTuple(double d);
		PhysTuple(bool b);
		const int getI() const;
		const bool getB() const;
		const double getD() const;
		const char getType() const;
		std::string to_string() const;
		std::string to_string_csv() const;

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
		friend std::ostream& operator << (std::ostream& out, PhysTuple tup);
};

#endif
