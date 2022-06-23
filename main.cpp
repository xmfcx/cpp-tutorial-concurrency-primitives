#include <atomic>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// a function that calculates pi to 1000 precision
double pi_calculator(int precision) {
  double pi = 0;
  for (int i = 0; i < precision; i++) {
    pi += (i % 2 == 0) ? -1.0 / (2 * i + 1) : 1.0 / (2 * i + 1);
  }
  return pi * 4;
}

int main() {

  // cout with 100000 precision
  std::cout << std::setprecision(100000);
  //  std::cout << "pi 1: " << pi_calculator(100000000) << std::endl;

  std::future<double> pi_future = std::async(std::launch::async, pi_calculator, 1000000000);
  std::future<double> pi_future2 = std::async(std::launch::async, pi_calculator, 100000000);
  std::future<double> pi_future3 = std::async(std::launch::async, pi_calculator, 10000000);

  std::cout << "doing other work" << std::endl;

  std::cout << "pi 1: " << pi_future.get() << std::endl;
  std::cout << "pi 2: " << pi_future2.get() << std::endl;
  std::cout << "pi 3: " << pi_future3.get() << std::endl;
}
