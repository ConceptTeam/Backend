### Preamble ###
cmake_minimum_required(VERSION 3.15)
project(database_test)

##### Project wide setup ####
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Dependencies ###

enable_testing()

add_executable(database_test main.cpp)

target_link_libraries(database_test GTest::gtest_main database)

include(GoogleTest)
gtest_discover_tests(database_test)
