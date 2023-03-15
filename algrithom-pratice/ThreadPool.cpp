#include "ThreadPool.h"
use namespace std;
ThreadPool::ThreadPool(int coreSize, int maxSize, int queueSize) {
  coreSize = coreSize;
  threads = new thread[coreSize];
  maxSize = maxSize;
  queueSize = queueSize;
}
ThreadPool::~ThreadPool() {
  delete threads;
  delete workQueue;
}
ThreadPool::start() {
  for (int i = 0; i < sizeof(threads); i++) {
  }
}

ThreadPool::commitTask() {}
