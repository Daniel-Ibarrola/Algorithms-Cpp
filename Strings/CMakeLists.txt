project(Strings)

set(HEADER_FILES
        SuffixTrees/pattern_trie.h
        SuffixTrees/multipattern_match.h
        SuffixTrees/suffix_tree.h
        SuffixTrees/suffix_trie.h
        BurrowsWheeler/burrows_wheeler.h
        )

set(SOURCE_FILES
        SuffixTrees/pattern_trie.cpp
        SuffixTrees/multipattern_match.cpp
        SuffixTrees/suffix_tree.cpp
        SuffixTrees/suffix_trie.cpp
        BurrowsWheeler/burrows_wheeler.cpp
        )

add_library(Strings STATIC ${SOURCE_FILES} ${HEADER_FILES})