//
// Created by daniel on 9/05/22.
//

#include "Refills.h"


int minRefills(int tankMax, const std::vector<int>& stops)
{
    int numRefills {0};
    int currentRefill {0};
    int lastRefill {0};
    int numberStops {static_cast<int>(stops.size()) - 2};

    while (currentRefill <= numberStops)
    {
        lastRefill = currentRefill;
        while ((currentRefill <= numberStops) &&
               stops[currentRefill + 1] - stops[lastRefill] <= tankMax)
            currentRefill += 1;

        if (currentRefill == lastRefill)
            return -1;

        if (currentRefill <= numberStops)
            numRefills += 1;

    }

    return numRefills;
}