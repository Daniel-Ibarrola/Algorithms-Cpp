project(np-complete)

set(HEADER_FILES
        coloring/graph_coloring.h
        hamiltonian_cycle/hamiltonian_cycle.h
        2-sat/2-sat.h
        independent_set/independent_set.h
        )

set(SOURCE_FILES
        coloring/graph_coloring.cpp
        hamiltonian_cycle/hamiltonian_cycle.cpp
        2-sat/2-sat.cpp
        independent_set/independent_set.cpp
        )

add_library(np-complete STATIC ${SOURCE_FILES} ${HEADER_FILES})