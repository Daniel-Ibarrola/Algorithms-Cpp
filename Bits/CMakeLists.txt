project(Bits)

set(HEADER_FILES
        bits.h
        )

set(SOURCE_FILES
        bits.cpp
        )

add_library(Bits STATIC ${SOURCE_FILES} ${HEADER_FILES})
