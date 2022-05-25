//
// Created by daniel on 25/05/22.
//

#include "gtest/gtest.h"
#include "DisjointSets/disjoint_sets.h"
#include <vector>

TEST(DisjointSetsTest, Constructor)
{
    DisjointSets djs(10);
    EXPECT_EQ(djs.parentSize(), 10);
    EXPECT_EQ(djs.ranKSize(), 10);
    EXPECT_EQ(djs.pathCompression(), false);
}

TEST(DisjointSetsTest, MakeSet)
{
    DisjointSets djs(5);
    for (int ii {0}; ii < 5; ++ii)
        djs.makeSet(ii);

    std::vector<int> parent {djs.getParent()};
    std::vector<int> rank {djs.getRank()};

    for (int ii {0}; ii < 5; ++ii)
    {
        EXPECT_EQ(parent[ii], ii);
        EXPECT_EQ(rank[ii], 0);
    }

}

class DisjointSetsNoPathCompression :  public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Set up the first disjoint sets
        for (int ii {0}; ii < 5; ++ii)
            djs_1.makeSet(ii);
        for (int ii {0}; ii < 4; ++ii)
            djs_1.setUnion(ii, ii + 1);

        // Set up the second disjoint sets
        for (int ii {0}; ii < 12; ++ii)
            djs_2.makeSet(ii);
        djs_2.setUnion(1, 9);
        djs_2.setUnion(6, 4);
        djs_2.setUnion(5, 0);
        djs_2.setUnion(2, 3);
        djs_2.setUnion(4, 10);
        djs_2.setUnion(6, 7);
        djs_2.setUnion(6, 2);
        djs_2.setUnion(11, 1);
        djs_2.setUnion(8, 5);
    }

    DisjointSets djs_1{5};
    DisjointSets djs_2{12};
};

TEST_F(DisjointSetsNoPathCompression, UnionByRank)
{
    // Tests for union by rank with no path compression
    std::vector<int> parent {1, 1, 1, 1, 1};
    std::vector<int> rank {0, 1, 0, 0, 0};
    EXPECT_EQ(djs_1.getParent(), parent);
    EXPECT_EQ(djs_1.getRank(), rank);

    parent = {0, 9, 3, 3, 3, 0, 4, 4, 0, 9, 4, 9};
    rank = {1, 0, 0, 2, 1, 0, 0, 0, 0, 1, 0, 0};
    EXPECT_EQ(djs_2.getParent(), parent);
    EXPECT_EQ(djs_2.getRank(), rank);
}

TEST_F(DisjointSetsNoPathCompression, FindNoCompression)
{
    // Tests for find with no path compression
    // Test first disjoint sets
    EXPECT_EQ(djs_1.find(0), 1);
    EXPECT_EQ(djs_1.find(1), 1);
    EXPECT_EQ(djs_1.find(2), 1);
    EXPECT_EQ(djs_1.find(3), 1);
    EXPECT_EQ(djs_1.find(4), 1);

    // Test second disjoint sets
    EXPECT_EQ(djs_2.find(0), 0);
    EXPECT_EQ(djs_2.find(1), 9);
    EXPECT_EQ(djs_2.find(2), 3);
    EXPECT_EQ(djs_2.find(3), 3);
    EXPECT_EQ(djs_2.find(4), 3);
    EXPECT_EQ(djs_2.find(5), 0);
    EXPECT_EQ(djs_2.find(6), 3);
    EXPECT_EQ(djs_2.find(7), 3);
    EXPECT_EQ(djs_2.find(8), 0);
    EXPECT_EQ(djs_2.find(9), 9);
    EXPECT_EQ(djs_2.find(10), 3);
    EXPECT_EQ(djs_2.find(11), 9);

}

TEST(DisjointSetsTest, FindPathCompression)
{
    std::vector<int> parent {5, 2, 4, 8, 4, 11, 9, 11, 4, 4, 5, 2};
    std::vector<int> rank {0, 0, 3, 0, 4, 1, 0, 0, 1, 1, 0, 2};

    ASSERT_EQ(parent.size(), rank.size());

    DisjointSets djs(parent, rank, true);
    djs.find(5);

    std::vector<int> newParent {5, 2, 4, 8, 4, 4, 9, 11, 4, 4, 5, 4};
    EXPECT_EQ(djs.getParent(), newParent);
}