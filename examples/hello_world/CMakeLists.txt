cmake_minimum_required(VERSION 3.5)

project(hello_world CXX)

add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world PRIVATE ztd)
target_include_directories(hello_world PRIVATE ../../include)
