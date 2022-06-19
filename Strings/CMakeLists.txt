project(Strings)

set(HEADER_FILES
        SuffixTrees/pattern_trie.h
        SuffixTrees/multipattern_match.h
        )

set(SOURCE_FILES
        SuffixTrees/pattern_trie.cpp
        SuffixTrees/multipattern_match.cpp
        )

add_library(Strings STATIC ${SOURCE_FILES} ${HEADER_FILES})