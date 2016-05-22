# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project (cubeapi)

# Include src CMakeList.txt
add_subdirectory(src)

# Bring the headers into the project
include_directories(include)

# Headers files and sources files 
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE TESTS "test/*.c")

# Compilers options
set(CMAKE_C_FLAGS "-O0 -std=c99")
set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11")

# Tests files
foreach( testsourcefile ${TESTS} )
    # simple string replace, to cut off .c.
    string( REPLACE ".c" "" testname ${testsourcefile})
    get_filename_component(FILE_NAME ${testsourcefile} NAME_WE)
    add_executable(${FILE_NAME} ${testsourcefile} ${HEADERS})
    target_link_libraries(${FILE_NAME} libcube)
endforeach( testsourcefile ${TESTS} )

# API documentation with Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
   configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

   add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)
