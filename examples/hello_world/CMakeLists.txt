cmake_minimum_required(VERSION 3.5)

project(hello_world CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_world hello_world.cpp)
target_link_libraries(hello_world PRIVATE zeta)
target_include_directories(hello_world PRIVATE ../../include)
