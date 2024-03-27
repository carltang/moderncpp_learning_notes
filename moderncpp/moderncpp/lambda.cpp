//
//  lambda.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/20.
//

#include "lambda.hpp"
#include <iostream>
/*
 [capture list] (parameter list) mutable(optional) exception attribute -> return type {
 // function body
 }
 [] empty capture list
 [name1, name2, ...] captures a series of variables
 [&] reference capture, let the compiler deduce the reference list by itself
 [=] value capture, let the compiler deduce the value list by itself
 */

void lambda_value_capture() {
	int value = 1;
	auto copy_value = [value] {
		return value;
	};
	value = 100;
	auto stored_value = copy_value();
	std::cout << "stored_value = " << stored_value << std::endl;
	// At this moment, stored_value == 1, and value == 100.
	// Because copy_value has copied when its was created.
}

void lambda_reference_capture() {
	int value = 1;
	auto copy_value = [&value] {
		return value;
	};
	value = 100;
	auto stored_value = copy_value();
	std::cout << "stored_value = " << stored_value << std::endl;
	// At this moment, stored_value == 100, value == 100.
	// Because copy_value stores reference
}

/*
 The value captures and reference captures mentioned above are variables that have been declared in the outer scope, so these capture methods capture the lvalue and not capture the rvalue.
 C++14 gives us the convenience of allowing the captured members to be initialized with arbitrary expressions, which allows the capture of rvalues
 */


void lambda_expression_capture() {
	// important is an exclusive pointer that cannot be caught by value capture using =. At this time we need to transfer it to the rvalue and initialize it in the expression
	auto important = std::make_unique<int>(1);
	auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
		return x+y+v1+(*v2);
	};
	std::cout << add(3,4) << std::endl;
}

//starting with C++14. The formal parameters of the lambda function can use the auto keyword to utilize template generics
auto add = [](auto x, auto y) {
	return x+y;
};

void lambda_test() {
	add(1, 2);
	add(1.1, 2.2);
}
