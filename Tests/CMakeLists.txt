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
        graph/test_weighted_digraph.cpp
        graph/test_weigthed_graph.cpp
        strings/test_pattern_trie.cpp
        strings/test_multipattern_match.cpp
        strings/test_suffix_tree_from_trie.cpp
        strings/test_suffix_tree.cpp
        strings/test_suffix_trie.cpp
        strings/test_burrow_wheeler.cpp
        strings/test_suffix_array.cpp
        strings/test_knuth_morris.cpp
        strings/test_sort_characters.cpp
        np-complete/test_graph_coloring.cpp
        np-complete/test_hamiltonian_cycle.cpp
        np-complete/test_2sat.cpp
        np-complete/test_independent_set.cpp
        np-complete/test_traveling_salesman.cpp
        )

# linking Google_Tests_run with my other libraries
target_link_libraries(Google_Tests_run DataStructures)
target_link_libraries(Google_Tests_run Graph)
target_link_libraries(Google_Tests_run Strings)
target_link_libraries(Google_Tests_run np-complete)
target_link_libraries(Google_Tests_run gtest gtest_main)