//
//  std::thread.cpp
//  moderncpp
//
//  Created by carltang on 2024/3/23.
//

#include "std_thread.hpp"
#include <thread>
#include <iostream>
#include <mutex>
#include <future>
#include <chrono>
#include <condition_variable>
#include <queue>

// std::mutex is the most basic mutex class in C++11, and you can create a mutex by instantiating std::mutex
// C++11 also provides a template class std::lock_guard for the RAII syntax for the mutex.
// RAII guarantees the exceptional security of the code while keeping the simplicity of the code.
int v = 1;

void critical_section(int change_v) {
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);

	// execute contention works
	v = change_v;

	// mtx will be released after leaving the scope
}

// td::unique_lock is more flexible than std::lock_guard.
// Objects of std::unique_lock manage the locking and unlocking operations on the mutex object with exclusive ownership
// std::lock_guard cannot explicitly call lock and unlock, and std::unique_lock can be called anywhere after the declaration. It can reduce the scope of the lock and provide higher concurrency
// If you use the condition variable std::condition_variable::wait you must use std::unique_lock as a parameter.
int v2 = 1;

void critical_section2(int change_v2) {
	static std::mutex mtx;
	std::unique_lock<std::mutex> lock(mtx);
	// 执行竞争操作
	v2 = change_v2;
	std::cout << v2 << std::endl;
	// 将锁进行释放
	lock.unlock();

	// 在此期间，任何人都可以抢夺 v 的持有权

	// 开始另一组竞争操作，再次加锁
	lock.lock();
	v2 += 1;
	std::cout << v2 << std::endl;
}

void test_std_thread() {
	// std::thread is used to create an execution thread instance
	// It provides a number of basic thread operations, such as get_id() to get the thread ID of the thread being created, use join() to join a thread
	std::thread t([](){
		std::cout << "hello world." << std::endl;
	});
	t.join();
	
	//mutex, lock_guard
	std::thread t1(critical_section, 2), t2(critical_section, 3);
	t1.join();
	t2.join();

	std::cout << v << std::endl;
	
	//unique_lock
	std::thread t3(critical_section2, 2), t4(critical_section2, 3);
		t3.join();
		t4.join();
	
	std::cout << v2 << std::endl;
}

void test_future() {
	//std::future
	// pack a lambda expression that returns 7 into a std::packaged_task
	std::packaged_task<int()> task([](){return 7;});
	// get the future of task
	std::future<int> result = task.get_future();    // run task in a thread
	std::thread(std::move(task)).detach();
	std::cout << "waiting...";
	result.wait(); // block until future has arrived
	// output result
	std::cout << "done!" << std:: endl << "future result is "
			  << result.get() << std::endl;
}

void test_condition_variable() {
	std::queue<int> produced_nums;
	std::mutex mtx;
	std::condition_variable cv;
	bool finished = false;
	bool notified = false;  // notification sign

	auto producer = [&]() {
		for (int i = 0; i < 30 ; i++) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			std::unique_lock<std::mutex> lock(mtx);
			std::cout << std::this_thread::get_id() << " producing " << i << std::endl;
			produced_nums.push(i);
			notified = true;
			cv.notify_all();
		}
		notified = true;
		finished = true;
	};
	auto consumer = [&]() {
		while (true) {
			std::unique_lock<std::mutex> lock(mtx);
			while (!notified) {  // avoid spurious wakeup
				cv.wait(lock);
			}

			// temporal unlock to allow producer produces more rather than
			// let consumer hold the lock until its consumed.
			lock.unlock();
			// consumer is slower
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			lock.lock();
			if (!produced_nums.empty()) {
				std::cout << std::this_thread::get_id() << " consuming " << produced_nums.front() << std::endl;
				produced_nums.pop();
			}
			notified = false;
			if (finished) {
				break;
			}
		}
	};
	const int CS_NUM = 2;

	std::thread p(producer);
	std::thread cs[CS_NUM];
	for (int i = 0; i < CS_NUM; ++i) {
		cs[i] = std::thread(consumer);
	}
	p.join();
	for (int i = 0; i < CS_NUM; ++i) {
		cs[i].join();
	}
}

/*Intuitively, it seems that a = 5; in t2 always executes before flag = 1; and while (flag != 1) in t1. It looks like there is a guarantee the line std ::cout << "b = " << b << std::endl; will not be executed before the mark is changed. Logically, it seems that the value of b should be equal to 5. But the actual situation is much more complicated than this*/
/*
 int a = 0;
 int flag = 0;

 std::thread t1([&]() {
	 while (flag != 1);

	 int b = a;
	 std::cout << "b = " << b << std::endl;
 });

 std::thread t2([&]() {
	 a = 5;
	 flag = 1;
 });

 t1.join();
 t2.join();
 */

struct A {
	float x;
	int y;
	long long z;
};

void test_atomic_operation() {
	std::atomic<int> count = {0};
	std::thread t1([&](){
		count.fetch_add(1);
	});
	std::thread t2([&](){
		count++;        // 等价于 fetch_add
		count += 1;     // 等价于 fetch_add
	});
	t1.join();
	t2.join();
	std::cout << count << std::endl;
	
	//通过 std::atomic<T>::is_lock_free 来检查该原子类型是否需支持原子操作
	std::atomic<A> a;
	std::cout << std::boolalpha << a.is_lock_free() << std::endl;
}

void test_memory_order() {
	// Relaxed model
	std::atomic<int> counter = {0};
	std::vector<std::thread> vt;
	for (int i = 0; i < 100; ++i) {
		vt.emplace_back([&](){
			counter.fetch_add(1, std::memory_order_relaxed);
		});
	}

	for (auto& t : vt) {
		t.join();
	}
	std::cout << "current counter:" << counter << std::endl;
	
	//Release/consumption model
	std::atomic<int*> ptr(nullptr);
	int v;
	std::thread producer([&]() {
		int* p = new int(42);
		v = 1024;
		ptr.store(p, std::memory_order_release);
	});
	std::thread consumer([&]() {
		int* p;
		while(!(p = ptr.load(std::memory_order_consume)));

		std::cout << "p: " << *p << std::endl;
		std::cout << "v: " << v << std::endl;
	});
	producer.join();
	consumer.join();
	
	//Release/Acquire model
	std::vector<int> vv;
	std::atomic<int> flag = {0};
	std::thread release([&]() {
		vv.push_back(42);
		flag.store(1, std::memory_order_release);
	});
	std::thread acqrel([&]() {
		int expected = 1; // must before compare_exchange_strong
		while(!flag.compare_exchange_strong(expected, 2, std::memory_order_acq_rel))
			expected = 1; // must after compare_exchange_strong
		// flag has changed to 2
	});
	std::thread acquire([&]() {
		while(flag.load(std::memory_order_acquire) < 2);

		std::cout << vv.at(0) << std::endl; // must be 42
	});
	release.join();
	acqrel.join();
	acquire.join();
	
	//Sequential Consistent Model
	std::atomic<int> counter4 = {0};
	std::vector<std::thread> vt4;
	for (int i = 0; i < 100; ++i) {
		vt4.emplace_back([&](){
			counter4.fetch_add(1, std::memory_order_seq_cst);
		});
	}

	for (auto& t : vt4) {
		t.join();
	}
	std::cout << "current counter:" << counter << std::endl;
}

void std_thread_test() {
	test_std_thread();
	test_future();
	test_condition_variable();
	test_atomic_operation();
	test_memory_order();
}
