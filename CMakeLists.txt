cmake_minimum_required(VERSION 3.22)
project(Algorithms)

set(CMAKE_CXX_STANDARD 14)

include_directories(ToolBox)
add_subdirectory(ToolBox)
include_directories(DataStructures)
add_subdirectory(DataStructures)
include_directories(Graph)
add_subdirectory(Graph)
include_directories(Strings)
add_subdirectory(Strings)

add_library(Algorithms library.cpp)
add_subdirectory(Tests)
