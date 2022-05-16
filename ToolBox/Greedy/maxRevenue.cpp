//
// Created by daniel on 9/05/22.
//

#include "maxRevenue.h"


long long maxRevenue(std::vector<int>& profit, std::vector<int>& clicks)
{
    long long revenue {0};
    std::sort(profit.begin(), profit.end());
    std::sort(clicks.begin(), clicks.end());

    for (auto ii {0}; ii < profit.size(); ++ii)
    {
        revenue += static_cast<long long>(profit[ii]) * clicks[ii];
    }

    return revenue;
}