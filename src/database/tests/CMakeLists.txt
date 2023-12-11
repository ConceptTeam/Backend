cmake_minimum_required(VERSION 3.14)
project(database_test)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# include the include folder one layer higher than this file
include_directories(${CMAKE_SOURCE_DIR}/../include)

# include the third party folder
include_directories(${CMAKE_SOURCE_DIR}/../../../third_party/sqlite_orm/include)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test_suite
  main.cpp
)
target_link_libraries(
    test_suite
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_suite)
