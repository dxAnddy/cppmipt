find_package(GTest REQUIRED)

function(add_cache_test NAME SOURCE_FILE)
    add_executable(${NAME} ${SOURCE_FILE})
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${NAME} cache_headers GTest::gtest GTest::gtest_main)
    message(STATUS "Built test ${NAME}")
endfunction()

if(BUILD_LRU)
    add_cache_test(test_lru_cache test_lru_cache.cpp)
endif()

if(BUILD_OPTIMAL)
    add_cache_test(test_opt_cache test_opt_cache.cpp)
endif()

if(BUILD_ARC)
    add_cache_test(test_arc_cache test_arc_cache.cpp)
endif()