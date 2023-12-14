cmake_minimum_required(VERSION 3.14)

project(database CXX)
set(CMAKE_CXX_STANDARD 17)

# target_compile_options(database INTERFACE -Wno-dev)

enable_testing()

# add_subdirectory(dependencies)
# add_subdirectory(src)

set(database_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(database INTERFACE)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../../thirdparty ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)

target_link_libraries(database INTERFACE sqlite_orm::sqlite_orm)

target_sources(database INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/database.hpp>)

target_include_directories(database INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

add_subdirectory(tests)
