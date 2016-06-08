set(WINDOWS_COMPILE 0 CACHE BOOL "Some user-specified option")
#Compile for Linux or Windows system
if(WINDOWS_COMPILE)
set(CMAKE_TOOLCHAIN_FILE ../Toolchain-cross-mingw32-linux.cmake)
endif(WINDOWS_COMPILE)

# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project(cubeAPILib C CXX)

find_package(Threads)

find_package(Boost COMPONENTS  python REQUIRED)
message("Include dirs of boost: " ${Boost_INCLUDE_DIRS} )
message("Libs of boost: " ${Boost_LIBRARIES} )

find_package(PythonLibs REQUIRED)
message("Include dirs of Python: " ${PYTHON_INCLUDE_DIRS} )
message("Libs of Python: " ${PYTHON_LIBRARIES} )


# Compilers options
set(CMAKE_C_FLAGS "-O0 -g -Wall -Werror -std=c99")
set(CMAKE_CXX_FLAGS "-O0 -g -Wall -Werror -std=c++11 -lpthread ")



# Bring the headers into the project
include_directories(../include)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})


# Headers files and sources files 
file(GLOB_RECURSE HEADERS "../include/*.h")
file(GLOB_RECURSE SOURCES_CXX "*.cpp")
file(GLOB_RECURSE SOURCES_C "*.c")


# Create cube api library

if(WINDOWS_COMPILE)
  add_library(cube ${SOURCES_CXX} ${SOURCES_C} ${HEADERS})
else(WINDOWS_COMPILE)
  add_library(cube SHARED ${SOURCES_CXX} ${SOURCES_C} ${HEADERS})
endif(WINDOWS_COMPILE)
