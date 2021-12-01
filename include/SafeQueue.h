#include <mutex>
#include <queue>

template <typename T>
class SafeQueue {
 private:
  std::queue<T> queue;
  std::mutex mutex;

 public:
  bool Empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return queue.empty();
  }
  int Size() {
    std::unique_lock<std::mutex> lock(mutex);
    return queue.size();
  }
  void EnQueue(T& t) {
    std::unique_lock<std::mutex> lock(mutex);
    queue.push(t);
  }
  bool Dequeue(T& t) {
    std::unique_lock<std::mutex> lock(mutex);
    if (queue.empty()) {
      return false;
    }
    t = queue.front();
    queue.pop();
    return true;
  }
};
