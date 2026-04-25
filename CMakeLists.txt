cmake_minimum_required(VERSION 3.10)
project(problem_077 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(code code.cpp)
# Header-only implementation in crossarray.hpp is included by code.cpp
