//
//  unorderedcontainer.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/21.
//

#include "unorderedcontainer.hpp"
#include <unordered_map>
#include <iostream>
#include <map>
/*
	std::map/std::set: These elements are internally implemented by red-black trees. The average complexity of inserts and searches is O(log(size)), C++11 introduces two unordered containers: std::unordered_map/std::unordered_multimap and std::unordered_set/std::unordered_multiset, The elements in the unordered container are not sorted, and the internals is implemented by the Hash table. The average complexity of inserting and searching for elements is O(constant)
*/
void unordered_container() {
	// initialized in same order
	std::unordered_map<int, std::string> u = {
		{1, "1"},
		{3, "3"},
		{2, "2"}
	};
	std::map<int, std::string> v = {
		{1, "1"},
		{3, "3"},
		{2, "2"}
	};

	// iterates in the same way
	std::cout << "std::unordered_map" << std::endl;
	for( const auto & n : u)
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

	std::cout << std::endl;
	std::cout << "std::map" << std::endl;
	for( const auto & n : v)
		std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
}
