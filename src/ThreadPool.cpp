#include "../include/ThreadPool.h"

#include <iostream>
ThreadPool::ThreadPool(const int num)
    : _threads(std::vector<std::thread>(num)), _shutdown(false) {}
void ThreadPool::init() {
  for (int i = 0; i < _threads.size(); i++) {
    _threads[i] = std::thread(ThreadWorker(i, this));
  }
}
void ThreadPool::shutdown() {
  _shutdown = true;
  _conditional_lock.notify_all();
  for (int i = 0; i < _threads.size(); i++) {
    if (_threads[i].joinable()) {
      _threads[i].join();
    }
  }
}
