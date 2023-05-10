//
// Created by daniel on 10/05/23.
//

#include "others.h"


int reverseDigits(int num)
{
    int remaining {abs(num)};
    int result {0};
    while (remaining > 0)
    {
        result = result * 10 + remaining % 10;
        remaining /= 10;
    }
    return num >= 0 ? result : -result;
}
