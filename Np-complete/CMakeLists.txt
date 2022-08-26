project(np-complete)

set(HEADER_FILES
        graph_coloring.h
        )

set(SOURCE_FILES
        graph_coloring.cpp
        )

add_library(np-complete STATIC ${SOURCE_FILES} ${HEADER_FILES})