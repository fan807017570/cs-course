/*===================================================
*	Copyright(c) 2023All rights reserved.
*
* file   name:ThreadPool.hpp
*      Author: miracle
* crete  date:20230303/15/23
* description:
*
=========================================================*/
#include <iostream>
#include <memory>
#include <pthread.h>
#include <string.h>
using namespace std;
template <class T>

class TaskWorker {
public:
  virtual void doWork();
  TaskWorker(T param);
  ~TaskWorker();
  T getWorkParam();

private:
  T param;
};
class ThreadPool {
public:
  ThreadPool(int coreSize, int maxSize, int queueSize);
  ~ThreadPool();

  void commitTask(TaskWorker &task);
  void shutDown();
  void stop();
  int getCoreThreadSize();
  int getMaxThreadSize();
  int getQueueSize();
  void start();

private:
  int coreSize;
  int maxSize;
  int queueSize;
  thread[] threads;
  vector<shared_ptr<TaskWorker>> workQueue;
};
