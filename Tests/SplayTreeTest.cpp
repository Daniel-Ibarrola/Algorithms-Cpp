//
// Created by daniel on 3/05/22.
//

#include "gtest/gtest.h"
#include "Bst/SplayTree.h"

TEST(SplayTree, EmptyTree)
{
    SplayTree tree;
    EXPECT_EQ(tree.isEmpty(), true);
}