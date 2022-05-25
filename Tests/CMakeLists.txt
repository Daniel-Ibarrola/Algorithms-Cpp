project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run test_heap.cpp test_heap_sort.cpp test_disjoint_sets.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run DataStructures)
target_link_libraries(Google_Tests_run gtest gtest_main)