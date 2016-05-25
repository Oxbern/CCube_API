# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project (cubeAPITest)

# Extern libraries required for compilation
find_package(Threads REQUIRED)
find_package(Curses REQUIRED)

FIND_PATH(LIBUSB_INCLUDE_DIR libusb.h
    HINTS $ENV{LIBUSB_ROOT}
    PATHS ${PC_LIBUSB_INCLUDEDIR} ${PC_LIBUSB_INCLUDE_DIRS}
    PATH_SUFFIXES include)

FIND_LIBRARY(LIBUSB_LIBRARIES NAMES usb-1.0
    HINTS $ENV{LIBUSB_ROOT}
    PATHS ${PC_LIBUSB_LIBDIR} ${PC_LIBUSB_LIBRARY_DIRS}
    PATH_SUFFIXES lib)


LINK_DIRECTORIES(../src)

# Headers files and sources files 
file(GLOB_RECURSE HEADERS "../include/*.h")
file(GLOB_RECURSE TESTS_C "*.c")
file(GLOB_RECURSE TESTS_CXX "*.cpp")

# Bring the headers into the project
include_directories(../include)
include_directories(${CURSES_INCLUDE_DIR})

# Tests files
# Change output directory for test files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exec)

foreach( testsourcefile ${TESTS_C})
    # simple string replace, to cut off .c.
    string( REPLACE ".c" "" testname ${testsourcefile})
    get_filename_component(FILE_NAME ${testsourcefile} NAME_WE)
    add_executable(${FILE_NAME} ${testsourcefile} ${HEADERS})
    target_link_libraries(${FILE_NAME} libcube ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES} )
endforeach( testsourcefile ${TESTS_C} )

foreach( testsourcefile ${TESTS_CXX})
    # simple string replace, to cut off .c.
    string( REPLACE ".cpp" "" testname ${testsourcefile})
    get_filename_component(FILE_NAME ${testsourcefile} NAME_WE)
    add_executable(${FILE_NAME} ${testsourcefile} ${HEADERS})
    target_link_libraries(${FILE_NAME} libcube ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES} usb)
endforeach( testsourcefile ${TESTS_CXX} )

# Target to execute all test files
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../test/tests.sh)
    add_custom_target(check
        COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../test/tests.sh)
endif()