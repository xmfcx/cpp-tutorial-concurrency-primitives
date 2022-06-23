#include <atomic>
#include <future>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class Cat {
 public:
  void ChangeName(const std::string &name) {
    std::lock_guard<std::mutex> lock(mutex_name_);
    name_ = name;
  }

  void PrintName() {
    std::lock_guard<std::mutex> lock(mutex_name_);
    std::cout << name_ << std::endl;
  }

 private:
  std::mutex mutex_name_;
  std::string name_;
};

int main() {
  Cat cat;

  std::thread name_changer([&cat]() {
    for (int i = 0; i < 10000000; ++i) {
      cat.ChangeName("caaaaaaaaaaaaat " + std::to_string(i));
    }
  });
  std::thread name_changer2([&cat]() {
    for (int i = 0; i < 10000000; ++i) {
      cat.ChangeName("doooooooooooooooog " + std::to_string(i));
    }
  });
  std::thread name_changer3([&cat]() {
    for (int i = 0; i < 10000000; ++i) {
      cat.ChangeName("giraffeeeeeeeeeeeeeeeeeee " + std::to_string(i));
    }
  });

  std::thread printer([&cat]() {
    while (true) {
      cat.PrintName();
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  });

  name_changer.join();
  name_changer2.join();
  printer.join();
}
