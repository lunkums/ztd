cmake_minimum_required(VERSION 3.5)

project(fizz_buzz CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fizz_buzz fizz_buzz.cpp)
target_link_libraries(fizz_buzz PRIVATE ztd)
target_include_directories(fizz_buzz PRIVATE ../../include)
