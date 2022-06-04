project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# adding the Google_Tests_run target
add_executable(Google_Tests_run
        data_structures/test_heap.cpp
        data_structures/test_heap_sort.cpp
        data_structures/test_disjoint_sets.cpp
        data_structures/test_hash_table.cpp
        data_structures/test_substring.cpp
        graph/test_adjacency_matrix.cpp
        graph/test_graph.cpp
        graph/test_digraph.cpp
        )

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(Google_Tests_run DataStructures)
target_link_libraries(Google_Tests_run Graph)
target_link_libraries(Google_Tests_run gtest gtest_main)