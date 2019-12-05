cmake_minimum_required(VERSION 3.5)

project(beauty)

# boost lib
find_package( Boost 1.58.0 COMPONENTS system thread program_options filesystem )
include_directories(${Boost_INCLUDE_DIRS})

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O3 -Wall ")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall ")
message ("cxx Flags: " ${CMAKE_CXX_FLAGS})

# Source code
include_directories("/home/$USER/include")
include_directories("./include")

file( GLOB APP_SOURCES "*.cpp" "*/*.cpp" )
foreach( sourcefile ${APP_SOURCES} )
    # executable name cut off .cpp
    string( REGEX REPLACE ".+/" "" executablename1 ${sourcefile} )
    string( REPLACE ".cpp" "" executablename ${executablename1} )

    message ("source files: " ${sourcefile} " executable: " ${executablename})
    add_executable( ${executablename} ${sourcefile} )
    target_link_libraries( ${executablename} pthread rt )
endforeach( sourcefile ${APP_SOURCES} )
