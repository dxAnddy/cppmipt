cmake_minimum_required(VERSION 3.10)
project(RANGE_QUERIES)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(range_queries_lib INTERFACE)
target_include_directories(range_queries_lib  INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_executable(rq ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(rq range_queries_lib)
message(STATUS "Built rq programm")

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building Tests")
    add_subdirectory(tests/unit)
endif()