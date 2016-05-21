cmake_minimum_required(VERSION 2.8.9)
project (main)

# Bring the headers, such as Student.h into the project
include_directories(include)
 
# However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTS "test/*.c")

set(CMAKE_C_FLAGS "-O0 -std=c99")
#set(SOURCE_FILES $(SOURCES))

add_executable(main ${SOURCES})
target_link_libraries(main m)
target_link_libraries(main ncurses)

#set(CMAKE_C_FLAGS "-O0 -std=c99 -Wall")
 

# Tests files
#foreach( testsourcefile ${TESTS} )
#    # simple string replace, to cut off .c.
#    string( REPLACE ".c" "" testname ${testsourcefile} )
#    add_executable( ${testname} ${testsourcefile} )
#endforeach( testsourcefile ${TESTS} )

add_library(connexion STATIC src/connexion.c)
add_library(crc STATIC src/crc.c)
add_library(cube STATIC src/cube.c)

add_executable(led_test test/led_test.c)
target_link_libraries(led_test connexion cube crc)

add_executable(data_encoding_test test/data_encoding_test.c)
target_link_libraries(data_encoding_test connexion crc)

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
