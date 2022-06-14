//
// Created by daniel on 14/06/22.
//

#include "validate_node.h"

void validateNode(int node, int numberOfNodes)
{
    // Check if a node is part of the graph
    if (node < 0 || node >= numberOfNodes)
        throw invalid_node_error();
}