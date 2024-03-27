//
//  smartpointer.hpp
//  moderncpp
//
//  Created by carltang on 2024/3/22.
//

#ifndef smartpointer_hpp
#define smartpointer_hpp

#include <stdio.h>
#include <memory>
#include <iostream>

void foo(std::shared_ptr<int> i) {
	(*i)++;
}

struct Foo {
	Foo()      { std::cout << "Foo::Foo" << std::endl;  }
	~Foo()     { std::cout << "Foo::~Foo" << std::endl; }
	void foo() { std::cout << "Foo::foo" << std::endl;  }
};

void f(const Foo &) {
	std::cout << "f(const Foo&)" << std::endl;
}

class A;
class B;

class A {
public:
	std::shared_ptr<B> pointer;
	~A() {
		std::cout << "A was destroyed" << std::endl;
	}
};
class B {
public:
	std::shared_ptr<A> pointer;
	~B() {
		std::cout << "B was destroyed" << std::endl;
	}
};


void smart_pointer_test() {
	/** std::shared_ptr   **/
	// auto pointer = new int(10); // illegal, no direct assignment
	// Constructed a std::shared_ptr
	
	//std::make_shared can be used to eliminate the explicit use of new
	auto pointer = std::make_shared<int>(10);
	foo(pointer);
	std::cout << *pointer << std::endl; // 11
	// The shared_ptr will be destructed before leaving the scope
	
	auto pointer2 = pointer; // reference count+1
	auto pointer3 = pointer; // reference count+1
	//get the raw pointer through the get()
	int *p = pointer.get();  // no increase of reference count

	//see the reference count of an object by use_count()
	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 3
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 3
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 3

	//reduce the reference count by reset()
	pointer2.reset();
	std::cout << "reset pointer2:" << std::endl;

	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 2
	std::cout << "pointer2.use_count() = "
		<< pointer2.use_count() << std::endl;                // pointer2 has reset, 0
	std::cout << "pointer3.use_count() = " << pointer3.use_count() << std::endl; // 2

	pointer3.reset();
	std::cout << "reset pointer3:" << std::endl;

	std::cout << "pointer.use_count() = " << pointer.use_count() << std::endl;   // 1
	std::cout << "pointer2.use_count() = " << pointer2.use_count() << std::endl; // 0
	std::cout << "pointer3.use_count() = "
		<< pointer3.use_count() << std::endl;                // pointer3 has reset, 0
	
	
	/** std::unique_ptr  **/
	std::unique_ptr<int> upointer = std::make_unique<int>(10); // make_unique, from C++14
	// std::unique_ptr<int> upointer2 = upointer; // illegal
	
	//C++11 does not provide std::make_unique, which can be implemented by yourself
	//template<typename T, typename ...Args>
	//std::unique_ptr<T> make_unique( Args&& ...args ) {
	//  return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
	//}
	
	std::unique_ptr<Foo> p1(std::make_unique<Foo>());

	// p1 is not empty, prints
	if (p1) p1->foo();
	{
		std::unique_ptr<Foo> p2(std::move(p1));

		// p2 is not empty, prints
		f(*p2);

		// p2 is not empty, prints
		if(p2) p2->foo();

		// p1 is empty, no prints
		if(p1) p1->foo();

		p1 = std::move(p2);

		// p2 is empty, no prints
		if(p2) p2->foo();
		std::cout << "p2 was destroyed" << std::endl;
	}
	// p1 is not empty, prints
	if (p1) p1->foo();
	// Foo instance will be destroyed when leaving the scope
	
	/** std::weak_ptr **/
	
	//The result is that A and B will not be destroyed, causes a memory leak
	std::shared_ptr<A> a = std::make_shared<A>();
	std::shared_ptr<B> b = std::make_shared<B>();
	a->pointer = b;
	b->pointer = a;
	
	//std::weak_ptr has no implemented * and -> operators, therefore it cannot operate on resources. std::weak_ptr allows us to check if a std::shared_ptr exists or not. The expired() method of a std::weak_ptr returns false when the resource is not released; Otherwise, it returns true. Furthermore, it can also be used for the purpose of obtaining std::shared_ptr, which points to the original object. The lock() method returns a std::shared_ptr to the original object when the resource is not released, or nullptr otherwise.
	
}

#endif /* smartpointer_hpp */
