//
//  deprecated.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/17.
//

#include "deprecated.hpp"

//在编写 C++ 时，也应该尽可能的避免使用诸如 void* 之类的程序风格。而在不得不使用 C 时，应该注意使用 extern "C" 这种特性，将 C 语言的代码与 C++代码进行分离编译，再统一链接这种做法,例如：
// foo.h
#ifdef __cplusplus
extern "C" {
#endif

int add(int x, int y);

#ifdef __cplusplus
}
#endif

// foo.c
int add(int x, int y) {
	return x+y;
}

// 1.1.cpp
//#include "foo.h"
#include <iostream>
#include <functional>

int ___main___() {
	[out = std::ref(std::cout << "Result from C code: " << add(1, 2))](){
		out.get() << ".\n";
	}();
	return 0;
}

void deprecated_test() {
	//不再允许字符串字面值常量赋值给一个 char *。如果需要用字符串字面值常量赋值和初始化一个 char *，应该使用 const char * 或者 auto
	char *str = "hello world";
	auto str2 = "hello world";
	/*
	异常说明、 unexpected_handler、set_unexpected() 等相关特性被弃用，应该使用 noexcept
	auto_ptr 被弃用，应使用 unique_ptr。
	register 关键字被弃用，可以使用但不再具备任何实际含义。
	bool 类型的 ++ 操作被弃用。
	如果一个类有析构函数，为其生成拷贝构造函数和拷贝赋值运算符的特性被弃用了。
	C 语言风格的类型转换被弃用（即在变量前使用 (convert_type)），应该使用 static_cast、reinterpret_cast、const_cast 来进行类型转换。
	特别地，在C++17标准中弃用了一些可以使用的 C 标准库，例如 <ccomplex>、<cstdalign>、<cstdbool> 与 <ctgmath> 等
	还有一些其他诸如参数绑定、export 等特性也均被弃用
	*/
	

}
