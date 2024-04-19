cmake_minimum_required(VERSION 3.5)

project(algorithms)

SET(CMAKE_CXX_FLAGS "-std=c++17 -O3 -s -Wall -Werror -Wno-class-memaccess")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror -Wno-class-memaccess")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

# Source code
include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(play)