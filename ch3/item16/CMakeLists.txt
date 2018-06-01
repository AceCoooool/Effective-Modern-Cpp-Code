cmake_minimum_required(VERSION 3.8)
project(item16)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads REQUIRED)
set(SOURCE_FILES main.cpp)
add_executable(item16 ${SOURCE_FILES})
target_link_libraries(item16 Threads::Threads)
