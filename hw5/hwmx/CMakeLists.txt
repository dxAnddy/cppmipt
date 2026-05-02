cmake_minimum_required(VERSION 3.10)
project(MATRIX)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_library(matrix_lib INTERFACE)
target_include_directories(matrix_lib INTERFACE include)

add_executable(matrix src/main.cpp)
target_link_libraries(matrix PRIVATE matrix_lib)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building tests")
    add_subdirectory(tests/unit)
endif()