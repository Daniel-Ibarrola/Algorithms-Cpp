project(Strings)

set(HEADER_FILES
        SuffixTrees/pattern_trie.h
        )

set(SOURCE_FILES
        SuffixTrees/pattern_trie.cpp
        )

add_library(Strings STATIC ${SOURCE_FILES} ${HEADER_FILES})