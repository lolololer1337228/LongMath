cmake_minimum_required(VERSION 3.24)
project(LongMath)

set(CMAKE_CXX_STANDARD 17)

add_executable(LongMath main.cpp LongInt.h LongInt.cpp LongDouble.h LongDouble.cpp)
