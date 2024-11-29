cmake_minimum_required(VERSION 3.28)
add_executable(tests listTest.cpp)
target_link_libraries(tests lsts_lib gtest gmock gtest_main gmock_main pthread)
