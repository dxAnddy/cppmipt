cmake_minimum_required(VERSION 3.10)
project(CACHE_PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lru_cache INTERFACE)
target_include_directories(lru_cache INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(lru_cache INTERFACE cxx_std_17)

add_executable(main_app ${CMAKE_SOURCE_DIR}/src/main.cpp)
target_link_libraries(main_app lru_cache)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building tests")
    add_subdirectory(tests/unit)
endif()