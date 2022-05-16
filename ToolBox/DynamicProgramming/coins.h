//
// Created by daniel on 10/05/22.
//

#ifndef ALGORITHMS_COINS_H
#define ALGORITHMS_COINS_H

#include <limits>
#include <vector>

int minNumberOfCoins(const std::vector<int>& denominations, int amount);

int minNumCoinsRec(const std::vector<int>& denominations, int amount, int index);

int numberCoinCombinations(const std::vector<int>& denominations, int amount);

#endif //ALGORITHMS_COINS_H
