//
// Created by daniel on 10/05/22.
//

#ifndef ALGORITHMS_SUBSETCOUNTER_H
#define ALGORITHMS_SUBSETCOUNTER_H

#include <iostream>
#include <utility>
#include <vector>

class wrong_method_error: public std::exception
{
    const char* what() const throw() override
    {
        return "The selected method is not supported";
    }
};

class SubsetCounter
{
private:
    std::vector<int> m_set;

    int countDp(int sum);

    int countRecursive(int sum, int item);

public:

    explicit SubsetCounter(std::vector<int> set) : m_set {std::move(set)}
    {

    }

    int count(int sum, char method='d');

    int setSum();

    int setsWithDifference(int diff);

    void clear() {m_set.clear();}

    void insert(int element) {m_set.push_back(element);}

};

#endif //ALGORITHMS_SUBSETCOUNTER_H
