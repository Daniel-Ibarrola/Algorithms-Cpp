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
    int num {11}; // 1011 in binary
    ASSERT_EQ(parity(num), 1);

    num = 136; // 10001000 in binary
    ASSERT_EQ(parity(num), 0);
}