# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project (cubeapi)

find_package(Threads)

# Headers files and sources files 
file(GLOB_RECURSE HEADERS "../include/*.h")
file(GLOB_RECURSE TESTS "*.c*")

LINK_DIRECTORIES(../src)

# Bring the headers into the project
include_directories(include)

# Tests files

# Change output directory for test files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

foreach( testsourcefile ${TESTS})
    # simple string replace, to cut off .c.
    string( REPLACE ".c" "" testname ${testsourcefile})
    get_filename_component(FILE_NAME ${testsourcefile} NAME_WE)
    add_executable(${FILE_NAME} ${testsourcefile} ${HEADERS})
    target_link_libraries(${FILE_NAME} libcube ${CMAKE_THREAD_LIBS_INIT})
endforeach( testsourcefile ${TESTS} )
