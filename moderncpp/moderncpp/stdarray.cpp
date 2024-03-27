//
//  stdarray.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/21.
//

#include "stdarray.hpp"
#include <vector>
#include <iostream>

// If the container size is fixed, then the std::array container can be used first.

void foo(int *p, int len) {
	return;
}

void std_array_test() {
	
	std::vector<int> v;
	std::cout << "size:" << v.size() << std::endl;         // output 0
	std::cout << "capacity:" << v.capacity() << std::endl; // output 0

	// As you can see, the storage of std::vector is automatically managed and
	// automatically expanded as needed.
	// But if there is not enough space, you need to redistribute more memory,
	// and reallocating memory is usually a performance-intensive operation.
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	std::cout << "size:" << v.size() << std::endl;         // output 3
	std::cout << "capacity:" << v.capacity() << std::endl; // output 4

	// The auto-expansion logic here is very similar to Golang's slice.
	v.push_back(4);
	v.push_back(5);
	std::cout << "size:" << v.size() << std::endl;         // output 5
	std::cout << "capacity:" << v.capacity() << std::endl; // output 8

	// As can be seen below, although the container empties the element,
	// the memory of the emptied element is not returned.
	v.clear();
	std::cout << "size:" << v.size() << std::endl;         // output 0
	std::cout << "capacity:" << v.capacity() << std::endl; // output 8
	// Additional memory can be returned to the system via the shrink_to_fit() call
	v.shrink_to_fit();
	std::cout << "size:" << v.size() << std::endl;         // output 0
	std::cout << "capacity:" << v.capacity() << std::endl; // output 0
	
	
	std::array<int, 4> arr = {1, 2, 3, 4};

	std::cout << arr.empty() << std::endl; // check if container is empty
	arr.size();  // return the size of the container

	// iterator support
	for (auto &i : arr)
	{
		// ...
	}

	// use lambda expression for sort
	std::sort(arr.begin(), arr.end(), [](int a, int b) {
		return b < a;
	});

	// array size must be constexpr
	constexpr int len = 4;
	std::array<int, len> arr2 = {1, 2, 3, 4};

	// illegal, different than C-style array, std::array will not deduce to T*
	// int *arr_p = arr;
	
	//C-style compatible interface. There are three ways to do this:
	
	// C-stype parameter passing
	// foo(arr, arr.size()); // illegal, cannot convert implicitly
	foo(&arr[0], arr.size());
	foo(arr.data(), arr.size());
	// use `std::sort`
	std::sort(arr.begin(), arr.end());
}
