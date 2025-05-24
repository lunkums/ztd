cmake_minimum_required(VERSION 3.5)

project(ztd CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# file(GLOB ZTD_SOURCES "src/*.cpp")
set(ZTD_SOURCES "src/fs/file.cpp" "src/io/writer.cpp" "src/io.cpp")

add_library(ztd STATIC ${ZTD_SOURCES})

target_include_directories(ztd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(examples)
