cmake_minimum_required(VERSION 2.8.9)
project (main)

#Bring the headers, such as Student.h into the project
include_directories(include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")
 
add_executable(main ${SOURCES})
