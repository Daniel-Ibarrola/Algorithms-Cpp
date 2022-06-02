project(Graph)

set(HEADER_FILES
        Graph/adjacency_list.h
        Graph/adjacency_matrix.h
        Digraph/digraph.h
        )

set(SOURCE_FILES
        Graph/adjacency_list.cpp
        Graph/adjacency_matrix.cpp
        Digraph/digraph.cpp
        )

add_library(Graph STATIC ${SOURCE_FILES} ${HEADER_FILES})