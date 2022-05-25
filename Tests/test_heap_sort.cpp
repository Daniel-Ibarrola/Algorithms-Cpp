//
// Created by daniel on 23/05/22.
//

#include <array>
#include "Heap/heap_sort.h"
#include "gtest/gtest.h"

TEST(TestHeapSort, BuildHeap)
{
    // Test with small array
    std::array<int, 3> arr {10, 20, 12};
    buildHeap(arr);
    EXPECT_EQ(arr[0], 20);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 12);

    // Test with another array
    std::array<int, 7> arr_2 {15, 25, 20, 30, 16, 13 ,14};
    buildHeap(arr_2);
    EXPECT_EQ(arr_2[0], 30);
    EXPECT_EQ(arr_2[1], 25);
    EXPECT_EQ(arr_2[2], 20);
    EXPECT_EQ(arr_2[3], 15);
    EXPECT_EQ(arr_2[4], 16);
    EXPECT_EQ(arr_2[5], 13);
    EXPECT_EQ(arr_2[6], 14);
}

TEST(TestHeapSort, SortArray)
{
    // Test with small array
    std::array<int, 5> arr_1 {20, 12, 14, 25, 8};
    std::array<int, 5> sorted_1 {8, 12, 14, 20, 25};
    heapSort(arr_1);
    EXPECT_EQ(arr_1, sorted_1);

    // Test with larger array
    std::array<int, 11> arr_2 {4, 15, 1, 13, 9, 20, 6, 5, 18, 2, 10};
    std::array<int, 11> sorted_2 {1, 2, 4, 5, 6, 9, 10, 13, 15, 18, 20};
    heapSort(arr_2);
    EXPECT_EQ(arr_2, sorted_2);
}