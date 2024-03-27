//
//  constants.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/17.
//

#include "constants.hpp"
#include <type_traits>
#include <iostream>

void foo(char *) {
	//std::cout << "foo(char*) is called" << std::endl;
	std::cout << __PRETTY_FUNCTION__ << " is called" << std::endl;
}
void foo(int i) {
	//std::cout << "foo(int) is called" << std::endl;
	std::cout << __PRETTY_FUNCTION__ << " is called" << std::endl;
}

#define LEN 10

int len_foo() {
	int i = 2;
	return i;
}
constexpr int len_foo_constexpr() {
	return 5;
}

//the function of constexpr can use recursion
constexpr int fibonacci(const int n) {
	return n == 1 || n == 2 ? 1 : fibonacci(n-1)+fibonacci(n-2);
}

//Starting with C++14, the constexpr function can use simple statements such as local variables, loops, and branches internally. the following code cannot be compiled under the C++11 standard
constexpr int fibonacci_2(const int n) {
	if(n == 1) return 1;
	if(n == 2) return 1;
	return fibonacci(n-1) + fibonacci(n-2);
}

void constants_test() {
	/*----- nullexpr -----*/
	//C++ does not allow to implicitly convert void * to other types, C++ without the void * implicit conversion has to define NULL as 0
	char * ch = NULL;
	
	//C++11 introduced the nullptr keyword, which is specifically used to distinguish null pointers, 0. The type of nullptr is nullptr_t
	
	//decltype is used for type derivation, and std::is_same is used to compare the equality of the two types
	if (std::is_same<decltype(NULL), decltype(0)>::value)
		std::cout << "NULL == 0" << std::endl;
	if (std::is_same<decltype(NULL), decltype((void*)0)>::value)
		std::cout << "NULL == (void *)0" << std::endl;
	if (std::is_same<decltype(NULL), std::nullptr_t>::value)
		std::cout << "NULL == nullptr" << std::endl;

	foo(0);          // will call foo(int)
	// foo(NULL);    // doesn't compile
	foo(nullptr);    // will call foo(char*)
	
	/*----- constexpr -----*/
	//C++11 provides constexpr to let the user explicitly declare that the function or object constructor will become a constant expression at compile time
	char arr_1[10];                      // 合法
	char arr_2[LEN];                     // 合法

	int len = 10;
	// char arr_3[len];                  // 非法

	const int len_2 = len + 1;
	constexpr int len_2_constexpr = 1 + 2 + 3;
	//the length of the array in the C++ standard must be a constant expression, and for len_2, this is a const constant, not a constant expression
	//char arr_4[len_2];                // 非法
	char arr_4[len_2_constexpr];         // 合法

	//before C++98 The compiler cannot know that len_foo() actually returns a constant at runtime, which causes illegal production.
	char arr_5[len_foo()+5];          // 非法
	char arr_6[len_foo_constexpr() + 1]; // 合法

	std::cout << fibonacci(10) << std::endl;
	// 1, 1, 2, 3, 5, 8, 13, 21, 34, 55
	std::cout << fibonacci(10) << std::endl;
	
}


