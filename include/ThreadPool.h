#ifndef THREADPOOL
#define THREADPOOL
#include <queue>

#include "SafeQueue.h"
class ThreadPool {
 private:
  bool shutdown;

 public:
  ThreadPool(/* args */);
  ~ThreadPool();
};
#endif