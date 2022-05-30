//
// Created by daniel on 21/05/22.
//

#include "gtest/gtest.h"
#include "Heap/heap.h"


class HeapTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        int arr[9] {42, 29, 18, 14, 7, 18,
                     12, 11, 13};
        for (int element : arr)
        {
            heap_1.insert(element);
            heap_2.insert(element);
            heap_3.insert(element);
        }
    }

    Heap heap_1{13};
    Heap heap_2{13};
    Heap heap_3{13};

};

TEST_F(HeapTest, IntegerConstructor)
{
    Heap h(10);
    EXPECT_EQ(h.isEmpty(), true);
    EXPECT_EQ(h.maxSize(), 10);
}

TEST_F(HeapTest, ArrayConstructor)
{
    int maxsize {13};
    int* arr{new int[maxsize] {42, 29, 28, 14, 7, 18,
                               12, 11, 5, 30, 29, 2,
                               8}};

    Heap heap(arr, maxsize, 9);
    EXPECT_EQ(heap.isEmpty(), false);
    EXPECT_EQ(heap.isFull(), false);
    EXPECT_EQ(heap.getPriority(0), 42);
    EXPECT_EQ(heap.getPriority(4), 7);
    EXPECT_EQ(heap.getPriority(7), 11);
}

TEST_F(HeapTest, GetParent)
{
    // Test get the parent of different elements
    int parent_inx {heap_1.parent(1)};
    EXPECT_EQ(parent_inx, 0);
    EXPECT_EQ(heap_1.getPriority(parent_inx), 42);

    parent_inx = heap_1.parent(3);
    EXPECT_EQ(parent_inx, 1);
    EXPECT_EQ(heap_1.getPriority(parent_inx), 29);

    parent_inx = heap_1.parent(6);
    EXPECT_EQ(parent_inx, 2);
    EXPECT_EQ(heap_1.getPriority(parent_inx), 18);

}

TEST_F(HeapTest, GetLeftChild)
{
    // Test get the left child of different elements
    int left_inx {heap_1.leftChild(1)};
    EXPECT_EQ(left_inx, 3);
    EXPECT_EQ(heap_1.getPriority(left_inx), 14);

    left_inx = heap_1.leftChild(3);
    EXPECT_EQ(left_inx, 7);
    EXPECT_EQ(heap_1.getPriority(left_inx), 11);
}

TEST_F(HeapTest, GetRightChild)
{
    // Test get the right child of different elements
    int right_inx {heap_1.rightChild(0)};
    EXPECT_EQ(right_inx, 2);
    EXPECT_EQ(heap_1.getPriority(right_inx), 18);

    right_inx = heap_1.rightChild(3);
    EXPECT_EQ(right_inx, 8);
    EXPECT_EQ(heap_1.getPriority(right_inx), 13);
}

TEST_F(HeapTest, InsertIntoHeap)
{
    // Insert elements into an empty heat
    Heap h(3);
    h.insert(10);
    h.insert(7);
    h.insert(5);
    ASSERT_EQ(h.isEmpty(), false);
    ASSERT_EQ(h.isFull(), true);
    EXPECT_EQ(h.getPriority(0), 10);
    EXPECT_EQ(h.getPriority(1), 7);
    EXPECT_EQ(h.getPriority(2), 5);

    // Insert elements into a non-empty heat
    heap_2.insert(16);
    ASSERT_EQ(heap_2.size(), 10);
    EXPECT_EQ(heap_2.getPriority(4), 16);

    heap_2.insert(50);
    ASSERT_EQ(heap_2.size(), 11);
    EXPECT_EQ(heap_2.getPriority(0), 50);

}

TEST_F(HeapTest, ExtractMax)
{
    // Test wit a small heap
    Heap h(3);
    h.insert(10);
    h.insert(7);
    h.insert(5);
    ASSERT_EQ(h.isEmpty(), false);
    EXPECT_EQ(h.extractMax(), 10);
    EXPECT_EQ(h.extractMax(), 7);
    EXPECT_EQ(h.extractMax(), 5);
    EXPECT_EQ(h.isEmpty(), true);

    // Test with another heap
    EXPECT_EQ(heap_3.extractMax(), 42);
    EXPECT_EQ(heap_3.extractMax(), 29);
    EXPECT_EQ(heap_3.extractMax(), 18);
    EXPECT_EQ(heap_3.extractMax(), 18);
    EXPECT_EQ(heap_3.extractMax(), 14);
    EXPECT_EQ(heap_3.extractMax(), 13);
    EXPECT_EQ(heap_3.extractMax(), 12);
    EXPECT_EQ(heap_3.extractMax(), 11);
    EXPECT_EQ(heap_3.extractMax(), 7);
    EXPECT_EQ(heap_3.isEmpty(), true);

}

TEST_F(HeapTest, RemoveFromHeap)
{
    // Test wit a small heap
    Heap h(3);
    h.insert(10);
    h.insert(7);
    h.insert(5);

    h.remove(2);
    EXPECT_EQ(h.size(), 2);

    h.remove(1);
    EXPECT_EQ(h.size(), 1);

    h.remove(0);
    EXPECT_EQ(h.isEmpty(), true);

    // Test with another heap
    int size {heap_3.size()};
    for (int ii {size - 1}; ii >= 0 ; --ii)
        heap_3.remove(ii);
    EXPECT_EQ(heap_3.isEmpty(), true);
}


TEST_F(HeapTest, SiftUp)
{
    int* arr {new int[5] {10, 8, 7, 20, -1}};
    Heap h(arr, 5, 4);
    h.siftUp(3);

    EXPECT_EQ(h.getPriority(0), 20);
    EXPECT_EQ(h.getPriority(1), 10);
    EXPECT_EQ(h.getPriority(2), 7);
    EXPECT_EQ(h.getPriority(3), 8);
}

TEST_F(HeapTest, SiftDowm)
{
    int* arr {new int[8] {12, 29, 18, 14, 7, 18, 11, 7}};
    Heap h(arr, 8, 8);
    h.siftDown(0);

    EXPECT_EQ(h.getPriority(0), 29);
    EXPECT_EQ(h.getPriority(1), 14);
    EXPECT_EQ(h.getPriority(2), 18);
    EXPECT_EQ(h.getPriority(3), 12);
    EXPECT_EQ(h.getPriority(4), 7);
    EXPECT_EQ(h.getPriority(5), 18);
    EXPECT_EQ(h.getPriority(6), 11);
    EXPECT_EQ(h.getPriority(7), 7);
}
