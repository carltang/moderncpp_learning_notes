//
//  bitfield.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/17.
//

#include "bitfield.hpp"
#include <iostream>

struct s {
	int i : 3 = 0;
	int j : 6 = 0;
};

void bitfield_test() {
	std::cout << sizeof(s) << std::endl;
}
