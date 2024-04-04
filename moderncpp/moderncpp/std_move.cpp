//
//  std_move.cpp
//  moderncpp
//
//  Created by carltang on 2024/4/3.
//

#include "std_move.hpp"
#include <iostream>
using namespace std;

/* move constructor/move assignment operator:
purpose: conveniently avoid costly and unnecessary deep copying.
 1. they are particularly powerful where passing by reference and passing by value are both used
 2. they give you finer control of which part of your object to be moved
 */

namespace TEST1 {
	void printInt(int& i) {cout << "lvalue reference: " << i << endl;}
	void printInt(int&& i) {cout << "rvalue reference: " << i << endl;}

	void simple_test() {
		int a = 5;
		printInt(a); // call printInt(int& i)
		printInt(6); // call printInt(int&& i)
	}
}

namespace TEST2 {
	class boVector {
		int size;
		double * arr_; // A big array
	public:
		boVector() {
			size = 0;
			arr_ = nullptr;
		}
		boVector(const boVector& rhs) { //copy constructor, deep copy
			size = rhs.size;
			arr_ = new double[size];
			for (int i= 0; i < size; i ++) {arr_[i] = rhs.arr_[i]; }
		}
		boVector(boVector&& rhs) { //move constructor, shallow copy
			size = rhs.size;
			arr_ = rhs.arr_;
			rhs.arr_ = nullptr;
		}
		~boVector() {delete arr_;}
	};
	void foo(boVector v) {cout << "pass value" << endl;}
	void foo_by_ref(boVector& v) {cout << "pass ref" << endl;}
	boVector createBoVecter() {
		boVector b;
		return b;
	}
}

namespace TEST3 {
//the most useful place for rvalue reference is overloading copy constructor and copy assignment operator
	class X {
		X& operator=(const X& rhs);
		X& operator=(X&& rhs);
	};
}

void std_test_test() {
	TEST1::simple_test();
	TEST2::boVector reusable = TEST2::createBoVecter();
	TEST2::foo(reusable); // copy constructor
	TEST2::foo_by_ref(reusable); // no constructor
	TEST2::foo(std::move(reusable)); // move constructor
	//reusable is distroyed here
	
}
