//
// Created by daniel on 10/05/23.
//

#include "bits.h"


int countBits(int num)
{
    int numBits {0};
    while (num)
    {
        numBits += num & 1;
        num >>= 1;
    }
    return numBits;
}

int parity(int num)
{
    // The parity of a binary number is 1 if the number of 1s is odd
    // otherwise it's 0.
    int result {0};
    while (num)
    {
        result ^= 1;
        num &= (num - 1); // drop the lowest set bit
    }
    return result;
}
