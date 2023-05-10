//
// Created by daniel on 10/05/23.
//

#include "gtest/gtest.h"
#include "others.h"


TEST(TestReverseDigits, PositiveNumber)
{
    int num {12345};
    ASSERT_EQ(reverseDigits(num), 54321);
}


TEST(TestReverseDigits, NegativeNumber)
{
    int num {-654321};
    ASSERT_EQ(reverseDigits(num), -123456);
}
