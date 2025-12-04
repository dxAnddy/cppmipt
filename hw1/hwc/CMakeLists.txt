cmake_minimum_required(VERSION 3.10)
project(CACHE_PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

option(BUILD_LRU "Build LRU Cache application" ON)
option(BUILD_OPTIMAL "Build Optimal cache application" ON)

add_library(cache_headers INTERFACE)
target_include_directories(cache_headers INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(cache_headers INTERFACE cxx_std_17)

add_executable(cache_lru ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_compile_definitions(cache_lru PRIVATE USE_LRU)
target_link_libraries(cache_lru cache_headers)
message(STATUS "Build LRU cache app: cache_lru")

add_executable(cache_opt ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_compile_definitions(cache_opt PRIVATE USE_OPTIMAL)
target_link_libraries(cache_opt cache_headers)
message(STATUS "Build Optimal cache app: cache_opt")

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building tests")
    add_subdirectory(tests/unit)
endif()