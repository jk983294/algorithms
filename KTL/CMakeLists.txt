cmake_minimum_required(VERSION 3.5)

project(KTL)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall ")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

add_executable(ktl src/main.cpp)
target_link_libraries(ktl KtlModule)

# Source code

add_subdirectory(src)
include_directories(src)
include_directories("/home/$USER/include")

add_subdirectory(test)
