//
//  oo.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/19.
//

#include "oo.hpp"
#include <iostream>

//C++11 introduces the concept of a delegate construct, which allows a constructor to call another constructor in a constructor in the same class
class Base {
public:
	int value1;
	int value2;
	Base() {
		value1 = 1;
	}
	Base(int value) : Base() { // delegate Base() constructor
		value2 = value;
	}
	
	virtual void foo(int) {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
	
	//final is to prevent the class from being continued to inherit and to terminate the virtual function to continue to be overloaded
	virtual void foo() final {
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}
};

//C++11 introduces the concept of inheritance constructors using the keyword using
class Subclass : public Base {
public:
	using Base::Base; // inheritance constructor
	
	//When overriding a virtual function, introducing the override keyword will explicitly tell the compiler to overload, and the compiler will check if the base function has such a virtual function with consistent function signature, otherwise it will not compile
	virtual void foo(int) override {
		std::cout << "Subclass::foo" << std::endl;
	}
	//virtual void foo(float) override; // illegal, no virtual function in super class
};

struct SubClass1 final: Base {
}; // legal

//struct SubClass2 : SubClass1 {
//}; // illegal, SubClass1 has final

//struct SubClass3: Base {
//	void foo(); // illegal, foo has final
//};

//C++11 allows explicit declarations to take or reject functions that come with the compiler
class Magic {
	public:
	Magic() = default; // explicit let compiler use default constructor
	Magic& operator=(const Magic&) = delete; // explicit declare refuse constructor
	Magic(int magic_number);
};


void oo_test() {
	Base b(2);
	std::cout << b.value1 << std::endl;
	std::cout << b.value2 << std::endl;
	
	Subclass s(3);
	std::cout << s.value1 << std::endl;
	std::cout << s.value2 << std::endl;
}
