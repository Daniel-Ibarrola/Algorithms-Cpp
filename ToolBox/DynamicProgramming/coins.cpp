//
// Created by daniel on 10/05/22.
//

#include "coins.h"


using table = std::vector<std::vector<int>>;
int infinity {std::numeric_limits<int>::max()};

int minNumberOfCoins(const std::vector<int>& denominations, int amount)
{
    // Returns the minimum number of coins to get a given amount
    // using the coin denominations in the vector denominations.
    int numCoins {static_cast<int>(denominations.size())};

    // Create a table to store results
    std::vector<int> row(amount + 1);
    table coinsTable (numCoins + 1, row);

    // For amount zero, zero coins are the minimum number
    for (int coin {0}; coin < numCoins + 1; ++coin)
        coinsTable[coin][0] = 0;
    // For zero coins and amount > 0 there is no minimum number
    for (int currentAmount {0}; currentAmount < amount + 1; ++currentAmount)
        coinsTable[0][currentAmount] = infinity;

    // Fill the table
    for (int coin {1}; coin < numCoins + 1; ++coin)
    {
        for (int currAmount {1}; currAmount < amount + 1; ++currAmount)
        {
            // Skip denomination if value is greater than current amount
            if (denominations[coin - 1] > currAmount)
                coinsTable[coin][currAmount] = coinsTable[coin - 1][currAmount];
            else
                // Check if the minimum value is including the current coin or excluding it
                coinsTable[coin][currAmount] = std::min(
                        coinsTable[coin -1 ][currAmount], // exclude denomination
                        1 + coinsTable[coin][currAmount - denominations[coin - 1]] // include
                );
        }
    }
    //print2DVector(coinsTable);
    // If it's not possible to get the amount with the given denominations
    // return -1
    if (coinsTable[numCoins][amount] == infinity)
        return -1;
    else
        return coinsTable[numCoins][amount];
}

int minNumCoinsRec(const std::vector<int>& denominations, int amount, int index)
{
    // Returns the minimum number of coins to get a given amount.
    // Slower algorithm that user a recursive call
    if (amount == 0)
        return 0;
    if (index >= denominations.size() || denominations[index] > amount)
        return 10e5;

    return std::min(minNumCoinsRec(denominations, amount, index + 1), // Exclude
                    1 + minNumCoinsRec(denominations, amount - denominations[index], index) // include
    );
}

int numberCoinCombinations(const std::vector<int>& denominations, int amount)
{
    // Count how many combinations of coins can give the desired amount.

    int numCoins {static_cast<int>(denominations.size())};
    // Create a table to store results
    std::vector<int> row (amount + 1, 0);
    table coinsTable(numCoins + 1, row);

    // For amount zero there is only one combination (the empty subset)
    for (int coin {0}; coin < numCoins + 1; ++coin)
        coinsTable[coin][0] = 1;

    // Fill the table
    for (int coin {1}; coin < numCoins + 1; ++coin)
    {
        for (int currAmount {1}; currAmount < amount + 1; ++currAmount)
        {
            // if coin value is greater than current amount, don't include
            // that denomination
            if (denominations[coin - 1] > currAmount)
                coinsTable[coin][currAmount] = coinsTable[coin - 1][currAmount];
            else
                // count add number of combinations by including and excluding
                // the current denomination
                coinsTable[coin][currAmount] = coinsTable[coin - 1][currAmount]
                                               + coinsTable[coin][currAmount - denominations[coin - 1]];
        }
    }
    return coinsTable[numCoins][amount];
}