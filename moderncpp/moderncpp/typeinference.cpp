//
//  typeinference.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/17.
//

#include "typeinference.hpp"
#include <iostream>

//Since C++ 20, auto can even be used as function arguments
int add(auto x, auto y) {
	return x+y;
}

// from C++14 it is possible to directly derive the return value of a normal function
template<typename T, typename U>
auto add3(T x, U y){
	return x + y;
}

//C++17 introduces the constexpr keyword into the if statement, allowing you to declare the condition of a constant expression in your code
template<typename T>
auto print_type_info(const T& t) {
	if constexpr (std::is_integral<T>::value) {
		return t + 1;
	} else {
		return t + 0.001;
	}
}

//decltype(auto) is a slightly more complicated use of C++14.
std::string  lookup1() {
	return "hello";
}
std::string dd = "world";

std::string& lookup2() {
	return dd;
}
decltype(auto) look_up_a_string_1() {
	return lookup1();
}
decltype(auto) look_up_a_string_2() {
	return lookup2();
}

void type_inference_test() {
	auto i = 5;              // i as int
	auto arr = new auto(10); // arr as int *
	std::cout << *arr << std::endl;
	
	auto j = 6; // type int
	std::cout << add(i, j) << std::endl;
	
	//auto cannot be used to derive array types yet
	//auto auto_arr2[10] = {arr};   // illegal, can't infer array type
	
	//The decltype keyword is used to solve the defect that the auto keyword can only type the variable.
	auto x = 1;
	auto y = 2;
	decltype(x+y) z;
	
	if (std::is_same<decltype(x), int>::value)
		std::cout << "type x == int" << std::endl;
	if (std::is_same<decltype(x), float>::value)
		std::cout << "type x == float" << std::endl;
	if (std::is_same<decltype(x), decltype(z)>::value)
		std::cout << "type z == type x" << std::endl;
	
	

}
