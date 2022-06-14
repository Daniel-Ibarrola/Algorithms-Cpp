//
// Created by daniel on 14/06/22.
//

#ifndef ALGORITHMS_VALIDATE_NODE_H
#define ALGORITHMS_VALIDATE_NODE_H

#include <iostream>

class invalid_node_error : public std::exception
{
    const char* what() const noexcept override
    {
        return "Invalid node";
    }
};

void validateNode(int node, int numberOfNodes);


#endif //ALGORITHMS_VALIDATE_NODE_H
