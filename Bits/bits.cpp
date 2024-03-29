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

int parity(unsigned long num)
{
    // The parity of a binary number is 1 if the number of 1s is odd
    // otherwise it's 0.
    num ^= num >> 32;
    num ^= num >> 16;
    num ^= num >> 8;
    num ^= num >> 4;
    num ^= num >> 2;
    num ^= num >> 1;
    return static_cast<int>(num & 0x1);
}


double power(double base, int exponent)
{
    double result {1.0};
    long long power = exponent;
    if (power < 0) {
        power = -power;
        base = 1.0 / base;
    }
    while (power) {
        if (power & 1) {
            result *= base;
        }
        base *= base;
        power >>= 1;
    }
    return result;
}
