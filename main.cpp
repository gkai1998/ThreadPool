#include <iostream>

#include "./include/ThreadPool.h"
int add(int a, int b) { return a + b; }
void multiply(int a, int b) {
  int res = a * b;
  std::cout << a << " * " << b << " = " << res << std::endl;
}
int main(int argc, const char** argv) {
  ThreadPool pool(3);
  pool.init();
  for (int i = 1; i < 3; ++i) {
    for (int j = 1; j < 10; ++j) {
      pool.submit(multiply, i, j);
    }
  }
  for (int i = 1; i < 3; ++i) {
    for (int j = 1; j < 10; ++j) {
      auto fu = pool.submit(add, i, j);
      int res = fu.get();
      std::cout << i << " + " << j << " = " << res << std::endl;
    }
  }
  //   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  pool.shutdown();
  return 0;
}