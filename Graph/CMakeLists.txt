project(Graph)

set(HEADER_FILES
        Graph/graph.h
        Graph/adjacency_matrix.h
        Digraph/digraph.h
        Digraph/weighted_digraph.h
        Graph/weighted_graph.h
        )

set(SOURCE_FILES
        Graph/graph.cpp
        Graph/adjacency_matrix.cpp
        Digraph/digraph.cpp
        Digraph/weighted_digraph.cpp
        Graph/weighted_graph.cpp
        )

add_library(Graph STATIC ${SOURCE_FILES} ${HEADER_FILES})