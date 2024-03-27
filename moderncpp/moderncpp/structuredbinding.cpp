//
//  structuredbinding.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/17.
//

#include "structuredbinding.hpp"
#include <iostream>
#include <tuple>
#include <map>

//C++11 has added a std::tuple container for constructing a tuple that encloses multiple return values
std::tuple<int, double, std::string> f() {
	return std::make_tuple(1, 2.3, "456");
}

template <typename Key, typename Value, typename F>
void update(std::map<Key, Value>& m, F foo) {
	for (auto& [key, value] : m ) value = foo(key);
}

template <typename Key, typename Value, typename F>
void update2(std::map<Key, Value>& m, F foo) {
	for (auto&& [key, value] : m ) value = foo(key);
}

void structured_binding_test() {
	auto [x, y, z] = f();
	std::cout << x << ", " << y << ", " << z << std::endl;
	
	std::map<std::string, long long int> m {
		{"a", 1},
		{"b", 2},
		{"c", 3}
	};
	update(m, [](std::string key) -> long long int {
		return std::hash<std::string>{}(key);
	});
	for (auto&& [key, value] : m)
		std::cout << key << ":" << value << std::endl;
}


