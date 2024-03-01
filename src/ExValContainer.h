#ifndef EX_VAL_CONTAINER_H_MFPG
#define EX_VAL_CONTAINER_H_MFPG

#include <ostream>
#include <iostream>

//Container for exclusive values, deals with access while ensuring correctness.
class ExValContainer {
	private:
		//Storage for possible fundamental types supported.
		union ExclusiveValue {
			public:
				explicit ExclusiveValue(int _i);
				explicit ExclusiveValue(bool _b);
				explicit ExclusiveValue(double _d);
				ExclusiveValue() = delete;
				int i;
				bool b;
				double d;
		};
		const ExclusiveValue ex_val;
		const char type; //Character representing which type is stored using typeid values.
	public:
		//Constructors are the only way to set the values.
		ExValContainer() = delete;
		ExValContainer(int i);
		ExValContainer(double d);
		ExValContainer(bool b);

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

		friend ExValContainer operator - (const ExValContainer lhs, const ExValContainer rhs);
		friend ExValContainer operator + (const ExValContainer lhs, const ExValContainer rhs);
		friend ExValContainer operator * (const ExValContainer lhs, const ExValContainer rhs);
		friend ExValContainer operator && (const ExValContainer lhs, const ExValContainer rhs);
		friend ExValContainer operator || (const ExValContainer lhs, const ExValContainer rhs);

		bool operator == (const ExValContainer& rhs) const;
		bool operator != (const ExValContainer& rhs) const;
		friend bool operator > (const ExValContainer& lhs, const ExValContainer& rhs);
		friend bool operator < (const ExValContainer& lhs, const ExValContainer& rhs);
		
		//Outputs the "to_string" string.
		friend std::ostream& operator << (std::ostream& out, ExValContainer tup);
};

#endif
