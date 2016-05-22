# CMake version
cmake_minimum_required(VERSION 2.8.9)

# Project Name
project(cubeAPILib)

# Compilers options
set(CMAKE_C_FLAGS "-O0 -std=c99")
set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11")

# Bring the headers into the project
include_directories(../include)

# Headers files and sources files 
file(GLOB_RECURSE HEADERS "../include/*.h")
file(GLOB_RECURSE SOURCES_CXX "*.cpp")
file(GLOB_RECURSE SOURCES_C "*.c")


# Create cube api library
add_library(libcube ${SOURCES_CXX} ${SOURCES_C} ${HEADERS})