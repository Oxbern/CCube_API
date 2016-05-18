cmake_minimum_required(VERSION 2.8.9)
project (main)

# Bring the headers, such as Student.h into the project
include_directories(include)
 
# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

# Add a target to generate API documentation with Doxygen
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

# C_FLAGS options
set(CMAKE_C_FLAGS "-O0 -std=c99")
 
add_executable(main ${SOURCES})
