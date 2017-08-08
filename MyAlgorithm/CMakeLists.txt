cmake_minimum_required(VERSION 3.5)

project(algorithms)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall ")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

# Source code

add_subdirectory(src)
include_directories(src)

add_subdirectory(test)