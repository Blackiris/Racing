find_package(GTest REQUIRED)

add_executable(racing_tests racing_lib/levelutil_tests.cpp)


target_link_libraries(racing_tests
    gtest::gtest
    gtest_main
    racing_lib
)

add_test(NAME racing_tests COMMAND racing_tests)
