//
//  enum.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/19.
//

#include "enum.hpp"
#include <iostream>

//C++11 introduces an enumeration class and declares it using the syntax of enum class
//In this syntax, the enumeration type is followed by a colon and a type keyword to specify the type of the enumeration value in the enumeration, which allows us to assign a value to the enumeration (int is used by default when not specified)
enum class new_enum : unsigned int {
	value1,
	value2,
	value3 = 100,
	value4 = 100
};

//we can overload the << operator to output, 没有完全看懂...
template<typename T>
std::ostream& operator<<(
	typename std::enable_if<std::is_enum<T>::value,
		std::ostream>::type& stream, const T& e)
{
	return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

void enum_test() {
	if (new_enum::value3 == new_enum::value4) { // true
		std::cout << "new_enum::value3 == new_enum::value4" << std::endl;
	}
	
	std::cout << new_enum::value3 << std::endl;
	
}
