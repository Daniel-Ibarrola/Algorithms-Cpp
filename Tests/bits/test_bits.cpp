//
// Created by daniel on 10/05/23.
//

#include "gtest/gtest.h"
#include "bits.h"


TEST(TestCountBits, ComputesCorrectNumber)
{
    int x {45}; // 101101 in binary
    ASSERT_EQ(countBits(x), 4);
}

TEST(TestParity, ComputesCorrectParity)
{
    unsigned long num {11}; // 1011 in binary
    ASSERT_EQ(parity(num), 1);

    num = 136; // 10001000 in binary
    ASSERT_EQ(parity(num), 0);
}

TEST(TestPower, ComputesCorrectValue)
{
    double base {2.5};
    int exponent {5};
    ASSERT_EQ(power(base, exponent), 97.65625);

    base = 5;
    exponent = 4;
    ASSERT_EQ(power(base, exponent), 625);
}

