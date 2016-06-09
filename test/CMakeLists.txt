set(WINDOWS_COMPILE 0 CACHE BOOL "Some user-specified option")
#Compile for Linux or Windows system
if(WINDOWS_COMPILE)
set(CMAKE_TOOLCHAIN_FILE ../Toolchain-cross-mingw32-linux.cmake)
endif(WINDOWS_COMPILE)

# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project (cubeAPITest C CXX)

# Extern libraries required for compilation
find_package(Threads REQUIRED)
if(NOT WINDOWS_COMPILE)
find_package(Curses REQUIRED)
endif(NOT WINDOWS_COMPILE)

# Compilers options
set(CMAKE_C_FLAGS "-O0 -g -Wall -Werror -std=c99 -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_FLAGS "-O0 -g -Wall -Werror -std=c++11 -static-libstdc++ -static-libgcc")

LINK_DIRECTORIES(../src)

# Headers files and sources files 
file(GLOB_RECURSE HEADERS "../include/*.h")
file(GLOB_RECURSE TESTS_C "CubicleTests/*.c" "UnitTests/*.c" "../samples/*.c")
file(GLOB_RECURSE TESTS_CXX "CubicleTests/*.cpp" "UnitTests/*.cpp" "../samples/*.cpp")

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
    target_link_libraries(${FILE_NAME} cube ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES} )
endforeach( testsourcefile ${TESTS_C} )

if(WINDOWS_COMPILE)
list(REMOVE_ITEM TESTS_CXX ${CMAKE_CURRENT_SOURCE_DIR}/CubicleTests/fd_test.cpp ${CMAKE_CURRENT_SOURCE_DIR}/CubicleTests/fd_test2.cpp)
endif(WINDOWS_COMPILE)

foreach( testsourcefile ${TESTS_CXX})
    # simple string replace, to cut off .c.
    string( REPLACE ".cpp" "" testname ${testsourcefile})
    get_filename_component(FILE_NAME ${testsourcefile} NAME_WE)
    add_executable(${FILE_NAME} ${testsourcefile} ${HEADERS})
    target_link_libraries(${FILE_NAME} cube ${CMAKE_THREAD_LIBS_INIT} ${CURSES_LIBRARIES}  )
    if(WINDOWS_COMPILE)
      target_link_libraries(${FILE_NAME}  ws2_32)
    endif(WINDOWS_COMPILE)
endforeach( testsourcefile ${TESTS_CXX} )

# Target to execute all test files
#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../test/tests.sh)
#    add_custom_target(check
#        COMMAND ${BASH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/../test/tests.sh)
#endif()
