//
// Created by daniel on 2/05/23.
//

#include "gtest/gtest.h"
#include "PriorityQueue/priority_queue.h"

std::vector<std::string> tasks {
        "Page load takes 2+ seconds",
        "UI breaks on browser",
        "Optional form field blocked",
        "CSS style causes misalignment",
        "CSS style causes 1px misalignment on browser X",
};

std::vector<int> priorities {
    7, 9, 1, 8, 5
};

TEST(PriorityQueue, InsertElement)
{
    PQHeap heap;
    heap.insert(tasks[0], priorities[0]);
    ASSERT_EQ(heap.peek(), tasks[0]);

    heap.insert(tasks[1], priorities[1]);
    ASSERT_EQ(heap.peek(), tasks[1]);

    heap.insert(tasks[2], priorities[2]);
    ASSERT_EQ(heap.peek(), tasks[1]);
    ASSERT_EQ(heap.size(), 3);
}

TEST(PriorityQueue, RemoveTopElement)
{
    PQHeap heap;
    heap.insert(tasks[0], priorities[0]);
    heap.insert(tasks[1], priorities[1]);
    heap.insert(tasks[2], priorities[2]);

    ASSERT_EQ(heap.top(), tasks[1]);
    ASSERT_EQ(heap.size(), 2);

    ASSERT_EQ(heap.top(), tasks[0]);
    ASSERT_EQ(heap.size(), 1);

    ASSERT_EQ(heap.top(), tasks[2]);
    ASSERT_TRUE(heap.empty());
}


TEST(PriorityQueue, RemoveElement)
{
    PQHeap heap;
    heap.insert(tasks[0], priorities[0]);
    heap.insert(tasks[1], priorities[1]);
    heap.insert(tasks[2], priorities[2]);

    heap.remove(tasks[0]);

    ASSERT_EQ(heap.size(), 2);
    ASSERT_EQ(heap.top(), tasks[1]);
    ASSERT_EQ(heap.top(), tasks[2]);
    ASSERT_TRUE(heap.empty());
}


TEST(PriorityQueue, UpdatePriority)
{
    PQHeap heap;
    heap.insert(tasks[0], priorities[0]);
    heap.insert(tasks[1], priorities[1]);
    heap.insert(tasks[2], priorities[2]);

    heap.update(tasks[2], 10);

    ASSERT_EQ(heap.peek(), tasks[2]);
}
