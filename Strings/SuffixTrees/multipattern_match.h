//
// Created by daniel on 19/06/22.
//

#ifndef ALGORITHMS_MULTIPATTERN_MATCH_H
#define ALGORITHMS_MULTIPATTERN_MATCH_H

#include "SuffixTrees/pattern_trie.h"

std::vector<int> findPatternPositions(const std::string& text,
                                      const std::vector<std::string>& patterns);

#endif //ALGORITHMS_MULTIPATTERN_MATCH_H
