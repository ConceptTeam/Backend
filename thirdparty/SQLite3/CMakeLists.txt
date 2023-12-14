cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SQLite3)

# Define the path to SQLite
set(SQLITE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Add all the source files to a variable
set(SQLITE_SOURCES
    ${SQLITE_PATH}/shell.c
    ${SQLITE_PATH}/sqlite3.c
)

# Add all the header files to a variable
set(SQLITE_HEADERS
    ${SQLITE_PATH}/sqlite3.h
    ${SQLITE_PATH}/sqlite3ext.h
)

# Add library target
add_library(SQLite3 ${SQLITE_SOURCES} ${SQLITE_HEADERS})

# Specify include directories for the library
target_include_directories(SQLite3 PUBLIC ${SQLITE_PATH})
