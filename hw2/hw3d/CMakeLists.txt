cmake_minimum_required(VERSION 3.10)
project(TRIANGLE_INTERSECTION_PROJECT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_library(geometry INTERFACE)
target_include_directories(geometry INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_executable(tri_inter ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(tri_inter geometry)
message(STATUS "Built tri_inter programm")

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building tests")
    add_subdirectory(tests/unit)
endif()