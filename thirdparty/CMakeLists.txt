set(CMAKE_WARN_DEPRECATED OFF)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_LIST_DIR}/SQLite3)

# Print cmake prefix path
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SQLite3)

# Print SQLite3 include directory
message(STATUS "SQLite3 include directory: ${SQLite3_INCLUDE_DIRS}")

add_subdirectory(sqlite_orm)
add_subdirectory(googletest)
