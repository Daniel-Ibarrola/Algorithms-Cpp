project(Advanced)

set(HEADER_FILES
        PriorityQueue/priority_queue.h
        )

set(SOURCE_FILES
        PriorityQueue/priority_queue.cpp
        )

add_library(Advanced STATIC ${SOURCE_FILES} ${HEADER_FILES})
