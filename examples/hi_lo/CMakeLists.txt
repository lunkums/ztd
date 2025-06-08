cmake_minimum_required(VERSION 3.5)

project(hi_lo CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hi_lo hi_lo.cpp)
target_link_libraries(hi_lo PRIVATE zeta)
target_include_directories(hi_lo PRIVATE ../../include)
