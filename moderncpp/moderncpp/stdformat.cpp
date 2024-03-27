//
//  stdformat.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/16.
//

#include "stdformat.hpp"
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <format>
#include <assert.h>

using namespace std;

// 100 -> 0x00000064
void format_example() {
	int n = 100;
	int pad = 10;
	printf("%#0*x\n", pad, n); //stdio
	cout << "0x" << setfill('0') << setw(pad-2) << hex << n << endl; //iostream
	cout << format("{:#010x}\n", n); //std::format
	
	
	double pi = 3.14159265358979;
	printf("%f\n", pi); // 输出3.141593，后面的被四舍五入了
	cout<<format("{}\n", pi); // format，输出完整的3.14159265358979

	// 与sprintf函数对应的是format_to_n
	char buff[50];
	sprintf(buff, "%f", pi);
	cout<<buff<<"\n"; // 与printf一样，输出3.141593
	format_to_n(buff, sizeof(buff), "{}", pi);
	cout<<buff<<"\n"; // 3.14159265358979
	
	//format_to
	vector<char> v;
	format_to(std::back_inserter(v), "{}", "1999"); // 输出到iterator
	// now v is {'1', '9', '9', '9'}
	assert(v[3] == '9');
	
	//back_inserter
	std::vector<int> vvv{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::fill_n(std::back_inserter(vvv), 3, -1);
	for (int n : vvv)
		std::cout << n << ' ';
	std::cout << '\n';
	//formatted_size
	auto size = std::formatted_size("{}", 42); // size == 2
	std::vector<char> buf(size); // 根据上面返回的size，将内存分配好
	std::format_to(buf.data(), "{}", 42);
}
