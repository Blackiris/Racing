include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#find_package(GTest REQUIRED)

add_executable(racing_tests racing_lib/levelutil_tests.cpp)


target_link_libraries(racing_tests
    gtest_main
    racing_lib
)

add_test(NAME racing_tests COMMAND racing_tests)
