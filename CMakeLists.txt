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

include_directories(Np-complete)
add_subdirectory(Np-complete)

include_directories(Advanced)
add_subdirectory(Advanced)

include_directories(Bits)
add_subdirectory(Bits)

include_directories(Others)
add_subdirectory(Others)

add_subdirectory(Tests)
