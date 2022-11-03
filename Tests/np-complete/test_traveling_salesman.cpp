//
// Created by daniel on 17/10/22.
//

#include "gtest/gtest.h"
#include "traveling_salesman/traveling_salesman.h"


class TravelingSalesmanTest : public ::testing::Test
{
protected:
    void SetUp() override
    {

    }

    std::vector<std::array<int, 3>> edgeList_1
    {
            {1, 2, 20},
            {1, 3, 42},
            {1, 4, 35},
            {2, 3, 30},
            {2, 4, 34},
            {3, 4, 12},
    };
    TSGraph graph_1 {4, edgeList_1};

    std::vector<std::array<int, 3>> edgeList_2
    {
            {1, 2, 1},
            {2, 3, 4},
            {3, 4, 5},
            {4, 2, 1},
    };
    TSGraph graph_2 {4, edgeList_2};

    std::vector<std::array<int, 3>> edgeList_3
    {
            {1, 2, 5},
            {1, 3, 1},
            {1, 4, 3},
            {1, 5, 2},
            {2, 3, 2},
            {2, 4, 3},
            {2, 5, 1},
            {3, 4, 2},
            {3, 5, 3},
            {4, 5, 4},
    };
    TSGraph graph_3 {5, edgeList_3};
};


TEST_F(TravelingSalesmanTest, TestCreateGraph)
{
    ASSERT_EQ(graph_1.numNodes(), 4);
    ASSERT_EQ(graph_1.numEdges(), 6);
}


TEST_F(TravelingSalesmanTest, GetEdgeWeight)
{
    ASSERT_EQ(graph_1.getWeight(0, 2), 42);
    ASSERT_EQ(graph_1.getWeight(2, 0), 42);
}


TEST_F(TravelingSalesmanTest, TravelingSalesmanPath)
{
    std::vector<int> expectedPath_1 {1, 4, 3, 2};
    ASSERT_EQ(graph_1.travelingSalesmanPath(), expectedPath_1);

    ASSERT_TRUE(graph_2.travelingSalesmanPath().empty());

    std::vector<int> expectedPath_3 {1, 3, 4, 2, 5};
    ASSERT_EQ(graph_3.travelingSalesmanPath(), expectedPath_3);
}


TEST_F(TravelingSalesmanTest, TravelingSalesmanWeight)
{
    ASSERT_EQ(graph_1.travelingSalesmanWeight(), 97);
    ASSERT_EQ(graph_2.travelingSalesmanWeight(), -1);
    ASSERT_EQ(graph_3.travelingSalesmanWeight(), 9);
}