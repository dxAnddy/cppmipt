find_package(GTest REQUIRED)

function(add_geometry_test NAME SOURCE_FILE)
    add_executable(${NAME} ${SOURCE_FILE})
    target_include_directories(${NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(${NAME} geometry_headers GTest::gtest GTest::gtest_main)
    message(STATUS "Built test ${NAME}")
endfunction()

add_geometry_test(test_point3d test_point3d.cpp)
add_geometry_test(test_vector3d test_vector3d.cpp)
add_geometry_test(test_triangle3d test_triangle3d.cpp)