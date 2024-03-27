//
//  tuples.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/22.
//

#include "tuples.hpp"

/*
 There are three core functions for the use of tuples:

 std::make_tuple: construct tuple
 std::get: Get the value of a position in the tuple
 std::tie: tuple unpacking
 */

#include <tuple>
#include <iostream>

template <typename T>
auto tuple_len(T &tpl) {
	return std::tuple_size<T>::value;
}

auto get_student(int id) {
	if (id == 0)
		return std::make_tuple(3.8, 'A', "John");
	if (id == 1)
		return std::make_tuple(2.9, 'C', "Jack");
	if (id == 2)
		return std::make_tuple(1.7, 'D', "Ive");

	// it is not allowed to return 0 directly
	// return type is std::tuple<double, char, std::string>
	return std::make_tuple(0.0, 'D', "null");
}

//这一段没看明白
//use std::variant<> (introduced by C++ 17) to provide type template parameters for variant<> You can have a variant<> to accommodate several types of variables provided
template <size_t n, typename... T>
constexpr std::variant<T...> _tuple_index(const std::tuple<T...>& tpl, size_t i) {
	if constexpr (n >= sizeof...(T))
		throw std::out_of_range("越界.");
	if (i == n)
		return std::variant<T...>{ std::in_place_index<n>, std::get<n>(tpl) };
	return _tuple_index<(n < sizeof...(T)-1 ? n+1 : 0)>(tpl, i);
}
template <typename... T>
constexpr std::variant<T...> tuple_index(const std::tuple<T...>& tpl, size_t i) {
	return _tuple_index<0>(tpl, i);
}
template <typename T0, typename ... Ts>
std::ostream & operator<< (std::ostream & s, std::variant<T0, Ts...> const & v) {
	std::visit([&](auto && x){ s << x;}, v);
	return s;
}

void tuples_test() {
	auto student = get_student(0);
		std::cout << "ID: 0, "
				  << "GPA: "   << std::get<0>(student) << ", "
				  << "Grade: " << std::get<1>(student) << ", "
				  << "Name: "  << std::get<2>(student) << '\n';

		double gpa;
		char grade;
		std::string name;

		// unpack tuples
		std::tie(gpa, grade, name) = get_student(1);
		std::cout << "ID: 1, "
				  << "GPA: "   << gpa << ", "
				  << "Grade: " << grade << ", "
				  << "Name: "  << name << '\n';
	//std::get In addition to using constants to get tuple objects, C++14 adds usage types to get objects in tuples
	std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
	std::cout << std::get<std::string>(t) << std::endl;
	//std::cout << std::get<double>(t) << std::endl; // illegal, runtime error
	std::cout << std::get<3>(t) << std::endl;
	
	//std::get<> depends on a compile-time constant, so the following is not legal:
	//int index = 1;
	//std::get<index>(t);
	
	int i = 1;
	std::cout << tuple_index(t, i) << std::endl;
	
	// merge two tuples
	auto new_tuple = std::tuple_cat(get_student(1), std::move(t));
	
	// iterate over the tuple
	for(int i = 0; i != tuple_len(new_tuple); ++i)
		// runtime indexing
		std::cout << tuple_index(new_tuple, i) << std::endl;
	
}
