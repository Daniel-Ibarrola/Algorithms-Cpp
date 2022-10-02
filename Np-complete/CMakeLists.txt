project(np-complete)

set(HEADER_FILES
        graph_coloring.h
        hamiltonian_cycle.h
        2-sat.h
        )

set(SOURCE_FILES
        graph_coloring.cpp
        hamiltonian_cycle.cpp
        2-sat.cpp
        )

add_library(np-complete STATIC ${SOURCE_FILES} ${HEADER_FILES})