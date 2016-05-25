# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project (cubeAPI C CXX)

# Compilers options
set(CMAKE_C_FLAGS "-O0 -g -Wall -Werror -std=c99")
set(CMAKE_CXX_FLAGS "-O0 -g -Wall -Werror -std=c++11")

# Bring the headers into the project
include_directories(include)

find_package(Threads REQUIRED)

# Include src and test CMakeList.txt
add_subdirectory(src)
add_subdirectory(test)

# API documentation with Doxygen
find_package(Doxygen)

if (DOXYGEN_FOUND)
   	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
   	${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile @ONLY)

    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )

    # Add generated files in clean target
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/html ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/latex ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)

endif(DOXYGEN_FOUND)
