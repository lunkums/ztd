cmake_minimum_required(VERSION 3.5)

project(allocators CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(allocators allocators.cpp)
target_link_libraries(allocators PRIVATE ztd)
target_include_directories(allocators PRIVATE ../../include)
