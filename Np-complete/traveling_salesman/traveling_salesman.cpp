//
// Created by daniel on 17/10/22.
//

#include "traveling_salesman.h"


std::vector<int> TSGraph::travelingSalesmanPath() const
{
    // Returns
    return {};
}


int TSGraph::travelingSalesmanWeight() const
{
    // Returns the optimal weight of the traveling salesman problem.

    int numSubsets {static_cast<int>(std::pow(2, numNodes()))};
    std::vector<std::vector<int>> cost(
            numSubsets,std::vector<int>(numNodes(),std::numeric_limits<int>::max()
            ));


    return 0;
}
