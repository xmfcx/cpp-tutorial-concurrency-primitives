cmake_minimum_required(VERSION 3.22)
project(concurrency_primitives)

set(CMAKE_CXX_STANDARD 17)

find_package(TBB REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

# link libtbb
target_link_libraries(${PROJECT_NAME} TBB::tbb)
