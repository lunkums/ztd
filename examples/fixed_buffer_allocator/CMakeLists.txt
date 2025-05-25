cmake_minimum_required(VERSION 3.5)

project(fixed_buffer_allocator CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(fixed_buffer_allocator fixed_buffer_allocator.cpp)
target_link_libraries(fixed_buffer_allocator PRIVATE ztd)
target_include_directories(fixed_buffer_allocator PRIVATE ../../include)
