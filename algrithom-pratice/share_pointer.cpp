/*===================================================
*	Copyright(c) 2023All rights reserved.
*
* file   name:share_pointer.cpp
*      Author: miracle
* crete  date:20230303/08/23
* description:
*
=========================================================*/
#include <iostream>
#include <memory>
using namespace std;
class Sample {
public:
  void dummyFunc() { cout << "dummyFunc " << endl; }
};

void base_test() {
  shared_ptr<Sample> ptr = make_shared<Sample>();
  (*ptr).dummyFunc();

  ptr->dummyFunc();

  shared_ptr<Sample> ptr2(ptr);

  if (ptr == ptr2) {
    cout << "ptr and ptr2 is equal" << endl;
  }

  shared_ptr<Sample> ptr3 = nullptr;
  if (!ptr3) {
    cout << "Yes ,ptr3 is empty" << endl;
  }
  if (ptr3 == NULL) {
    cout << "ptr3 is empty" << endl;
  }
  if (ptr3 == nullptr) {
    cout << "ptrs is empty" << endl;
  }

  Sample *rawPtr = ptr.get();
  rawPtr->dummyFunc();
}

class Base {
public:
  Base() { cout << "Base::Base()\n" << endl; }
  ~Base() { cout << "base::~Base()\n" << endl; }
};

class Derived : public Base {
public:
  Derived() { cout << "Derived::Derived()\n" << endl; }
  ~DErived()(cout << "DErived::~Derived()\n" << endl;)
}

void print(auto rem,shared_ptr<Base> const& sp){
  cout << rem << "\n\tget()=" << sp.get() << ",use_count()=" << sp.use_count()
       << endl;
}

void th_func(shared_ptr<Base> sp) {
  this_thread::sleep(987ms);
  shared_ptr<Base> lp = sp;
  mutex io_mutex;
  lock_guard<mutex> lk(io);
  print("Local pointer in a thread:", lp);
}

int main() { base_test(); }
