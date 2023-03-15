/*===================================================
*	Copyright(c) 2023All rights reserved.
*
* file   name:thread_example.cpp
*      Author: miracle
* crete  date:20230303/08/23
* description:
*
=========================================================*/
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
void fun1(int n) {
  for (int i = 0; i < 5; i++) {
    cout << "Thread 1 exectuiing \n" << endl;
    ++n;
    this_thread::sleep_for(chrono::milliseconds(10));
  }
}

void fun2(int &n) {
  for (int i = 0; i < 5; i++) {
    cout << "thread 2 executing \n" << endl;
    ++n;
    this_thread::sleep_for(chrono::milliseconds(10));
  }
}
class foo {
public:
  int n = 0;
  void bar() {
    for (int i = 0; i < 5; i++) {
      cout << "thread 3 executing \n" << endl;
      ++n;
      this_thread::sleep_for(chrono::milliseconds(10));
    }
  }
};
class baz {
public:
  void operator()() {
    cout << "thread 3 executing \n" << endl;
    ++n;
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  int n = 0;
};
int main() {
  int n = 0;
  foo f;
  baz b;
  thread t1;
  thread t2(fun1, n + 1);
  thread t3(fun2, ref(n)); // pass by reference
  thread t4(move(t3));
  thread t5(&foo::bar, &f);
  thread t6(b);
  t2.join();
  t4.join();
  t5.join();
  t6.join();
  cout << "Final value of n is " << n << endl;
  cout << "final value of f.n is  " << f.n << endl;
  cout << "Final value of b.n is " << b.n << endl;
}
