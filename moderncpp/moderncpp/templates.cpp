//
//  templates.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/18.
//

#include "templates.hpp"
#include <vector>
#include <map>
#include <iostream>

//C++11 introduces an external template that extends the syntax of the original mandatory compiler to instantiate a template at a specific location, allowing us to explicitly tell the compiler when to instantiate the template
//template class std::vector<bool>;          // force instantiation
extern template class std::vector<double>; // should not instantiation in current file

//In traditional C++, typedef can define a new name for the type, but there is no way to define a new name for the template. Because the template is not a type.

template<typename T, typename U>
class MagicType {
public:
	T dark;
	U magic;
};

// not allowed
//template<typename T>
//typedef MagicType<std::vector<T>, std::string> FakeDarkMagic;

//C++11 uses using to introduce the following form of writing, and at the same time supports the same effect as the traditional typedef
typedef int (*process)(void *); //old style
using NewProcess = int(*)(void *); // new style
template<typename T>
using TrueDarkMagic = MagicType<std::vector<T>, std::string>; //wonderful

//variadic templates
//C++11 added a new representation, allowing any number, template parameters of any category, and there is no need to fix the number of parameters when defining
template<typename... Ts> 
class Magic {
	
};

class Magic<int,
			std::vector<int>,
			std::map<std::string,
			std::vector<int>>> darkMagic;

class Magic<> nothing;

//If you do not want to generate 0 template parameters, you can manually define at least one template parameter:
template<typename Require, typename... Args> class Magic_at_least_1_par;

//C++11 can also make printf-like functions naturally handle objects that are not self-contained
template<typename... Args> void printf(const std::string &str, Args... args);

//we can use sizeof... to calculate the number of arguments
template<typename... Ts>
void magic(Ts... args) {
	std::cout << sizeof...(args) << std::endl;
}

// recursively traversing all template parameters
template<typename T0>
void printf1(T0 value) {
	std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args) {
	std::cout << value << std::endl;
	printf1(args...);
}

// Added support for variable parameter template expansion in C++17, so you can write printf in a function
template<typename T0, typename... T>
void printf2(T0 t0, T... t) {
	std::cout << t0 << std::endl;
	if constexpr (sizeof...(t) > 0) printf2(t...);
}

// expanded using the initialization list, 没完全看懂...
template<typename T, typename... Ts>
auto printf3(T value, Ts... args) {
	std::cout << value << std::endl;
	(void) std::initializer_list<T>{([&args] {
		std::cout << args << std::endl;
	}(), value)...};
}

template<typename ... T>
auto sum(T ... t) {
	return (t + ...);
}

template<typename ... T>
auto mean(T... t) {
	return (t + ...) / sizeof...(t);
}

void template_test() {
	TrueDarkMagic<bool> you;
	//We can pass any number of arguments to the magic function
	magic();      // 0
	magic(1);     // 1
	magic(1, ""); // 2
	
	printf1(1, 2, "123", 1.1);
	printf2(1, 2, "123", 1.1);
	printf3(1, 2, "123", 1.1);
	std::cout << sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
	std::cout << mean(1, 2, 3, 4, 5, 6) << std::endl;
}
