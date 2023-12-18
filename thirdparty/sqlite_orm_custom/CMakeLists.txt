# CMake file for compiling the sqlite3 static library under Windows (for ease of use)
#
# Copyright (c) 2012-2023 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT)

set(sqlite_orm_VERSION "1.8.0")
set(PACKAGE_VERSION ${sqlite_orm_VERSION})

project("sqlite_orm" VERSION ${PACKAGE_VERSION})

# Handling C++ standard version to use
option(SQLITE_ORM_ENABLE_CXX_20 "Enable C++ 20" OFF)
option(SQLITE_ORM_ENABLE_CXX_17 "Enable C++ 17" OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(SQLITE_ORM_ENABLE_CXX_20)
    set(CMAKE_CXX_STANDARD 20)
    message(STATUS "SQLITE_ORM: Build with C++20 features")
elseif(SQLITE_ORM_ENABLE_CXX_17)
    set(CMAKE_CXX_STANDARD 17)
    message(STATUS "SQLITE_ORM: Build with C++17 features")
else()
    # fallback to C++14 if there is no special instruction
    set(CMAKE_CXX_STANDARD 14)
    message(STATUS "SQLITE_ORM: Build with C++14 features")
endif()
set(CMAKE_CXX_EXTENSIONS OFF)


set(SQLITE_ENABLE_COLUMN_METADATA ON)

# add sources of the "sqlite3" static library
add_library(sqlite3
 sqlite3.c
 sqlite3.h
)

if (WIN32)
    if (BUILD_SHARED_LIBS)
            add_definitions("-DSQLITE_API=__declspec(dllexport)")
    endif()
endif()

add_library(SQLite::SQLite3 ALIAS sqlite3)

target_include_directories(sqlite3
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/>)

if (SQLITE_ENABLE_COLUMN_METADATA)
    # Enable the use of SQLite column metadata method
    # Require that the sqlite3 library is also compiled with this flag:
    target_compile_definitions(sqlite3 PUBLIC SQLITE_ENABLE_COLUMN_METADATA)
endif (SQLITE_ENABLE_COLUMN_METADATA)

# if (SQLITE_ENABLE_RTREE)
#     # Enable RTree extension when building sqlite3
#     # See more here: https://sqlite.org/rtree.html
#     target_compile_definitions(sqlite3 PUBLIC SQLITE_ENABLE_RTREE)
#     message(STATUS "Compile sqlite3 with SQLITE_ENABLE_RTREE")
# endif (SQLITE_ENABLE_RTREE)

# if (SQLITE_ENABLE_DBSTAT_VTAB)
#     # Enable DBSTAT extension when building sqlite3
#     # See more here: https://www.sqlite.org/dbstat.html
#     target_compile_definitions(sqlite3 PUBLIC SQLITE_ENABLE_DBSTAT_VTAB)
#     message(STATUS "Compile sqlite3 with SQLITE_ENABLE_DBSTAT_VTAB")
# endif (SQLITE_ENABLE_DBSTAT_VTAB)

if (UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))
    set_target_properties(sqlite3 PROPERTIES COMPILE_FLAGS "-fPIC")

    # Put each function in its own section to allow the linker garbage
    # collection to remove unused section and produced a smaller
    # statically-lined executables.
    target_compile_options(sqlite3 PRIVATE "-ffunction-sections")
endif (UNIX AND (CMAKE_COMPILER_IS_GNUCXX OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang"))

if (UNIX AND CMAKE_COMPILER_IS_GNUCXX)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 7.0)
        target_compile_options(sqlite3 PRIVATE "-Wimplicit-fallthrough=0")
    endif()
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 8.0)
        target_compile_options(sqlite3 PRIVATE "-Wno-cast-function-type")
    endif()
endif()

# Allow the library to be installed via "make install" and found with "find_package"

include(GNUInstallDirs)
install(TARGETS sqlite3
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT libraries)
install(FILES sqlite3.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} COMPONENT headers)

### Main Build Targets
set(SqliteOrm_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
add_library(sqlite_orm INTERFACE)
add_library(sqlite_orm::sqlite_orm ALIAS sqlite_orm)

# find_package(SQLite3 REQUIRED)
target_link_libraries(sqlite_orm INTERFACE SQLite::SQLite3)

target_sources(sqlite_orm INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/sqlite_orm/sqlite_orm.h>)

target_include_directories(sqlite_orm INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
