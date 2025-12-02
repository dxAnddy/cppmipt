find_package(GTest REQUIRED)

add_executable(test_lru_cache test_lru_cache.cpp)

target_include_directories(test_lru_cache PRIVATE  ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(test_lru_cache lru_cache GTest::gtest GTest::gtest_main)

