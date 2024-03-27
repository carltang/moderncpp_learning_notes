//
//  functionwrapper.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/20.
//

#include "functionwrapper.hpp"


#include <iostream>
#include <functional>

using foo = void(int);  // function pointer
void functional(foo f) {
	f(1);
}

int ff(int para) {
	return para;
}

int fff(int a, int b, int c) {
	return a + b - c;
}

void function_object_wrapper_test() {
	auto f = [](int value) {
		std::cout << value << std::endl;
	};
	functional(f);  // call by function pointer
	f(1);           // call by lambda expression
	
	std::function<int(int)> func = ff;

	int important = 10;
	std::function<int(int)> func2 = [&](int value) -> int {
	   return 1+value+important;
	};
	std::cout << func(10) << std::endl;
	std::cout << func2(10) << std::endl;
	
	// bind parameter 1, 2 on function fff,
	// and use std::placeholders::_1 as placeholder for the first parameter.
	auto bindFoo = std::bind(fff, std::placeholders::_1, 1,2);
	// when call bindFoo, we only need one param left
	std::cout << bindFoo(1) << std::endl;
}
