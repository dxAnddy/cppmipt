cmake_minimum_required(VERSION 3.10)
project(CACHE_PROJECT)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

option(BUILD_LRU "Build LRU Cache application" ON)
option(BUILD_OPTIMAL "Build Optimal cache application" ON)
option(BUILD_ARC "Build Arc cache implementation" ON)

add_library(cache_headers INTERFACE)
target_include_directories(cache_headers INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_features(cache_headers INTERFACE cxx_std_17)

function(add_cache_binary NAME MACRO)
    add_executable(${NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
    target_compile_definitions(${NAME} PRIVATE ${MACRO})
    target_link_libraries(${NAME} cache_headers)
    message(STATUS "Build cache app: ${NAME}")
endfunction()

if(BUILD_LRU)
    add_cache_binary(cache_lru USE_LRU)
endif()

if(BUILD_OPTIMAL)
    add_cache_binary(cache_opt USE_OPTIMAL)
endif()

if(BUILD_ARC)
    add_cache_binary(cache_arc USE_ARC)
endif()

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    message(STATUS "Building tests")
    add_subdirectory(tests/unit)
endif()