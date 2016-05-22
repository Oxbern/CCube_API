# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project (cubeAPITest)

# Compilers options
set(CMAKE_C_FLAGS "-O0 -std=c99")
set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11")

# Bring the headers into the project
include_directories(include)

# Include src CMakeList.txt
add_subdirectory(src)
add_subdirectory(test)

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
