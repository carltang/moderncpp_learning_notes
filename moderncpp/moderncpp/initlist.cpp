//
//  initlist.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/17.
//

#include "initlist.hpp"

#include <iostream>
#include <vector>

// before C++11
class Foo {
public:
	int value_a;
	int value_b;
	Foo(int a, int b) : value_a(a), value_b(b) {}
};

//after c++11
/*
 C++11 first binds the concept of the initialization list to the type and calls it std::initializer_list, allowing the constructor or other function to use the initialization list like a parameter, which is the initialization of class objects provides a unified bridge between normal arrays and PODPlain Old Data, i.e. classes without constructs, destructors, and virtual functions) initialization methods
 */
class MagicFoo {
public:
	std::vector<int> vec;
	//initialize list constructor,
	MagicFoo(std::initializer_list<int> list) {
		for (std::initializer_list<int>::iterator it = list.begin();
			 it != list.end(); ++it)
			vec.push_back(*it);
	}
	//the initialization list can also be used as a formal parameter of a normal function
	void foo(std::initializer_list<int> list) {
			for (std::initializer_list<int>::iterator it = list.begin();
				it != list.end(); ++it) vec.push_back(*it);
	}
};


void initlist_test() {
	// before C++11
	int arr[3] = {1, 2, 3};
	Foo foo(1, 2);
	std::vector<int> vec = {1, 2, 3, 4, 5};

	std::cout << "arr[0]: " << arr[0] << std::endl;
	std::cout << "foo:" << foo.value_a << ", " << foo.value_b << std::endl;
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
		std::cout << *it << std::endl;
	}
	
	// after C++11
	MagicFoo magicFoo = {1, 2, 3, 4, 5};

	std::cout << "magicFoo: ";
	for (std::vector<int>::iterator it = magicFoo.vec.begin();
		it != magicFoo.vec.end(); ++it)
		std::cout << *it << std::endl;
	magicFoo.foo({6,7,8,9});
	
	//C++11 also provides a uniform syntax for initializing arbitrary objects
	Foo foo2 {3, 4};
	
}
