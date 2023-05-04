//
// Created by daniel on 2/05/23.
//

#ifndef ALGORITHMS_PRIORITY_QUEUE_H
#define ALGORITHMS_PRIORITY_QUEUE_H

#include <string>
#include <vector>

struct Task
{
    std::string element;
    int priority;

    friend bool operator== (const Task& t1, const Task& t2);
};


class EmptyHeapError : public std::exception
{
public:
    const char * what() const noexcept override {
      return "Heap is empty";
    };
};


class PQHeap
{
    // A priority queue implemented with a heap
private:
    std::vector<Task> m_tasks;

    void bubbleUp(std::size_t index);
    void pushDown(std::size_t index);
    static std::size_t getParentIndex(std::size_t index);
    std::size_t getFirstLeafIndex() const;
    std::size_t highestPriorityChild(std::size_t parentIndex) const;

public:

    PQHeap() = default;

    void insert(const std::string& task, int priority);
    std::string peek() const;
    std::string top();
    void remove(const std::string& task);
    void update(const std::string& task, int priority);

    bool empty() const { return m_tasks.empty(); }
    std::size_t size() const { return m_tasks.size(); }

};


#endif //ALGORITHMS_PRIORITY_QUEUE_H
