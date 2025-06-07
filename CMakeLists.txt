cmake_minimum_required(VERSION 3.5)

project(ztd CXX)

# Set minimum CXX standard
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# HACK: Set maximum CXX standard with specific compiler flags. Only works for
# some compilers.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  message(STATUS "Clang compiler detected. Adding -std=c++98 -pedantic-errors.")
  add_compile_options(-std=c++98 -pedantic-errors)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  message(
    STATUS "GNU (GCC) compiler detected. Adding -std=c++98 -pedantic-errors.")
  add_compile_options(-std=c++98 -pedantic-errors)
elseif(MSVC)
  message(
    STATUS "MSVC compiler detected. Direct -std=c++98 not directly applicable.")
endif()

# file(GLOB ZTD_SOURCES "src/*.cpp")
set(ZTD_SOURCES "src/fs/file.cpp" "src/io/writer.cpp" "src/debug.cpp"
                "src/io.cpp" "src/posix.cpp")

add_library(ztd STATIC ${ZTD_SOURCES})

target_include_directories(ztd PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(ztd PRIVATE cxx_std_98)

add_subdirectory(examples)
