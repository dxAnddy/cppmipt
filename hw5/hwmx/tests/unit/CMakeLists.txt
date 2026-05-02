find_package(GTest REQUIRED)

function(add_matrix_test NAME SOURCE_FILE)
    add_executable(${NAME} ${SOURCE_FILE})
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${NAME} matrix_lib GTest::gtest GTest::gtest_main)
endfunction()

add_matrix_test(test_matrix test_matrix.cpp)