project(Others)

set(HEADER_FILES
        others.h
        )

set(SOURCE_FILES
        others.cpp
        )

add_library(Others STATIC ${SOURCE_FILES} ${HEADER_FILES})
