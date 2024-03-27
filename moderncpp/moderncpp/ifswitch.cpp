//
//  ifswitch.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/17.
//

#include "ifswitch.hpp"
#include <vector>
#include <iostream>

void ifswitch_test() {
	std::vector<int> vec = {1, 2, 3, 4};

	//since c++17, can be simplified by using `auto`
	const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
	if (itr != vec.end()) {
		*itr = 3;
	}
	//since C++17, declare a temporary variable in the if and switch statements
	if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
		*itr = 4;
	}
	
	//注意：if括号里，语句之间用分号
	if (auto itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
		*itr = 4;
	}

	// should output: 1, 4, 3, 4. can be simplified using `auto`
	for (auto element = vec.begin(); element != vec.end(); ++element)
		std::cout << *element << std::endl;
}
