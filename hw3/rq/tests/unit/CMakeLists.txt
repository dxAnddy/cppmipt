find_package(GTest REQUIRED)

function(rq_test NAME SOURCE_FILE)
    add_executable(${NAME} ${SOURCE_FILE})
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${NAME} range_queries_lib GTest::gtest GTest::gtest_main)
    message(STATUS "Built test ${NAME}")
endfunction()

rq_test(test test_parse.cpp)
