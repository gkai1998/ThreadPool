#ifndef THREADPOOL
#define THREADPOOL
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

#include "SafeQueue.h"
class ThreadPool {
 private:
  bool _shutdown;
  SafeQueue<std::function<void()>> _queue;
  std::vector<std::thread> _threads;
  std::mutex _mutex;
  std::condition_variable _conditional_lock;
  class ThreadWorker {
   private:
    int id;
    ThreadPool *pool;

   public:
    ThreadWorker(int wid, ThreadPool *threadpool) : id(wid), pool(threadpool){};
    void operator()() {
      std::function<void()> func;
      while (!(pool->_shutdown)) {
        std::unique_lock<std::mutex> lock(pool->_mutex);
        if (pool->_queue.Empty()) {
          pool->_conditional_lock.wait(lock);
        }
        bool issuccess = pool->_queue.Dequeue(func);
        if (issuccess) {
          func();
        }
      }
    }
  };

 public:
  ThreadPool(const int num);
  void init();
  void shutdown();
  template <typename F, typename... Args>
  auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>{
      {std::function<decltype(f(args...))()> func =
           std::bind(std::forward<F>(f), std::forward<Args>(args)...);
  auto task_ptr =
      std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
  std::function<void()> wrapper_func = [task_ptr]() { (*task_ptr)(); };
  _queue.EnQueue(wrapper_func);
  _conditional_lock.notify_one();
  return task_ptr->get_future();
}
}
;
}
;
#endif