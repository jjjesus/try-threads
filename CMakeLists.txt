cmake_minimum_required(VERSION 3.15)
project(mythreads)

set(CMAKE_CXX_STANDARD 11)

add_executable(mythreads main.cpp ThreadPool.cpp ThreadPool.h)
target_link_libraries(mythreads pthread)
