cmake_minimum_required(VERSION 3.8)
project(extra1)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp range_own.h)
add_executable(extra1 ${SOURCE_FILES})
