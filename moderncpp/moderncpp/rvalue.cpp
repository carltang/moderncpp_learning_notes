//
//  rvalue.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/20.
//

#include "rvalue.hpp"
#include <type_traits>
#include <string>
#include <iostream>
#include <utility>
#include <vector>

void reference(std::string& str) {
	std::cout << "lvalue" << std::endl;
}
void reference(std::string&& str) {
	std::cout << "rvalue" << std::endl;
}

//test move semantics
class A {
public:
	int *pointer;
	A():pointer(new int(1)) {
		std::cout << "construct" << pointer << std::endl;
	}
	A(A& a):pointer(new int(*a.pointer)) {
		std::cout << "copy" << pointer << std::endl;
	} // meaningless object copy
	A(A&& a):pointer(a.pointer) {
		a.pointer = nullptr;
		std::cout << "move" << pointer << std::endl;
	}
	~A(){
		std::cout << "destruct" << pointer << std::endl;
		delete pointer;
	}
};
// avoid compiler optimization
A return_rvalue(bool test) {
	A a,b;
	if(test) return a; // equal to static_cast<A&&>(a);
	else return b;     // equal to static_cast<A&&>(b);
}

void rvalue_test() {
	
	//这一段没搞太懂，const char[] 是lvalue，但const char*是rvalue?
	// a literal (except a string literal) is a prvalue. However, a string literal is an lvalue with type const char array
	// Correct. The type of "01234" is const char [6], so it is an lvalue
	const char (&left)[6] = "01234";
	
	// Assert success. It is a const char [6] indeed. Note that decltype(expr)
	// yields lvalue reference if expr is an lvalue and neither an unparenthesized
	// id-expression nor an unparenthesized class member access expression.
	static_assert(std::is_same<decltype("01234"), const char(&)[6]>::value, "");
	
	// Error. "01234" is an lvalue, which cannot be referenced by an rvalue reference
	// const char (&&right)[6] = "01234";
	
	
	//an array can be implicitly converted to a corresponding pointer.The result, if not an lvalue reference, is an rvalue
	const char*   p    = "01234"; // Correct. "01234" is implicitly converted to const char*
	const char*&& pr   = "01234"; // Correct. "01234" is implicitly converted to const char*, which is a prvalue.
	// const char*& pl = "01234"; // Error. There is no type const char* lvalue
	
	
	//C++11 provides the std::move method to unconditionally convert lvalue parameters to rvalues.
	std::string  lv1 = "string,";       // lv1 is a lvalue
	// std::string&& r1 = lv1;          // illegal, rvalue can't ref to lvalue
	std::string&& rv1 = std::move(lv1); // legal, std::move can convert lvalue to rvalue
	std::cout << rv1 << std::endl;      // string,
	reference(rv1); //output: lvalue
	reference(std::forward<std::string>(rv1)); //output: rvalue
	
	const std::string& lv2 = lv1 + lv1; // legal, const lvalue reference can
	// extend temp variable's lifecycle
	// lv2 += "Test";                   // illegal, const ref can't be modified
	std::cout << lv2 << std::endl;      // string,string,
	
	std::string&& rv2 = lv1 + lv2;      // legal, rvalue ref extend lifecycle
	rv2 += "string";                    // legal, non-const reference can be modified
	std::cout << rv2 << std::endl;      // string,string,string,string
	
	reference(std::forward<std::string>(rv2)); // outout: rvalue
	reference(rv2);                     // output: lvalue
	
	// int &a = std::move(1); // illegal, non-const lvalue reference cannot ref rvalue
	const int &b = std::move(1); // legal, const lvalue reference can
	
	A obj = return_rvalue(false);
	std::cout << "obj:" << std::endl;
	std::cout << obj.pointer << std::endl;
	std::cout << *obj.pointer << std::endl;
	
	std::string str = "Hello world.";
	std::vector<std::string> v;
	
	// use push_back(const T&), copy
	v.push_back(str);
	// "str: Hello world."
	std::cout << "str: " << str << std::endl;
	
	// use push_back(const T&&),
	// no copy the string will be moved to vector,
	// and therefore std::move can reduce copy cost
	v.push_back(std::move(str));
	// str is empty now
	std::cout << "str: " << str << std::endl;
	
	
	//Why is auto&& the safest way to use looping statements? Because when auto is pushed to a different lvalue and rvalue reference, the collapsed combination with && is perfectly forwarded
}
