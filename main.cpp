#include <atomic>
#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// prints elements of vector
void print(const std::vector<std::atomic_int> &v, const std::string &name) {
  std::cout << name << ": ";
  for (const auto &i: v)
    std::cout << i << " ";
  std::cout << std::endl;
}

int main() {
  // vector of numbers 1 to 10000
  std::vector<std::atomic<int>> numbers(10);
  for (int i = 0; i < numbers.size(); ++i)
    numbers[i] = i + 1;

  // create a mutex
  std::mutex m_println;
  auto println_protected = [](const std::string &text) {
    std::cout << text << std::endl;
  };

  auto make_x = [println_protected, &m_println](
                    std::vector<std::atomic_int> &numbers,
                    int x,
                    size_t ind_start,
                    size_t ind_end,
                    const std::string &name) {
    for (size_t i = ind_start; i <= ind_end; i++) {
      numbers[i] = x;
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
  };

  // print numbers
  print(numbers, "numbers");

  std::thread t1(make_x, std::ref(numbers), 1, 0, 9, "ahmet");
  std::thread t2(make_x, std::ref(numbers), 2, 0, 9, "mehmet");

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  std::cout << "threads are still ongoing" << std::endl;

  t1.join();
  std::cout << "t1 joined" << std::endl;
  t2.join();
  std::cout << "t2 joined" << std::endl;

  // print numbers
  print(numbers, "numbers");
}
