#include <future>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// prints elements of vector
void print(const std::vector<int> &v, const std::string &name) {
  std::cout << name << ": ";
  for (auto i: v)
    std::cout << i << " ";
  std::cout << std::endl;
}

int main() {

  // vector of numbers 1 to 10
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // create a mutex
  std::mutex m_println;
  auto println_protected = [](const std::string &text) {
    std::cout << text << std::endl;
  };

  auto make_x = [println_protected, &m_println](
                    std::vector<int> &numbers,
                    int x,
                    size_t ind_start,
                    size_t ind_end,
                    const std::string &name) {
    for (size_t i = ind_start; i <= ind_end; i++) {
      int old_num = numbers[i];
      numbers[i] = x;
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));

      {
        std::lock_guard<std::mutex> lock(m_println);
        println_protected("modified index #" + std::to_string(i)
                          + " from " + std::to_string(old_num)
                          + " to " + std::to_string(x));
      }

    }
  };

  // print numbers
  print(numbers, "numbers");

  std::thread t1(make_x, std::ref(numbers), 200, 0, 4, "ahmet");
  std::thread t2(make_x, std::ref(numbers), 500, 5, 9, "mehmet");

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  std::cout << "threads are still ongoing" << std::endl;

  t1.join();
  std::cout << "t1 joined" << std::endl;
  t2.join();
  std::cout << "t2 joined" << std::endl;
}
