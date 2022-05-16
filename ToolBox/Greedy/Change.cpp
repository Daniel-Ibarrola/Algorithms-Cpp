//
// Created by daniel on 9/05/22.
//

#include "Change.h"

int getChange(int money) {
    int numberOfCoins {0};
    while (money)
    {
        if (money >= 10)
            money -= 10;
        else if (money >= 5)
            money -= 5;
        else
            money -= 1;
        numberOfCoins++;
    }
    return numberOfCoins;
}