cmake_minimum_required(VERSION 3.5)

project(fizz_buzz CXX)

add_executable(fizz_buzz fizz_buzz.cpp)
target_link_libraries(fizz_buzz PRIVATE ztd)
target_include_directories(fizz_buzz PRIVATE ../../include)
