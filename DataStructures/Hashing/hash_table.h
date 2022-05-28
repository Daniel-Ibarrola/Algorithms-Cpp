//
// Created by daniel on 26/05/22.
//

#ifndef ALGORITHMS_HASH_TABLE_H
#define ALGORITHMS_HASH_TABLE_H

#include <algorithm>
#include <string>
#include <vector>

class HashTable
{
private:
    long long multiplier {263};
    long long prime {1000000007};
    std::vector<std::vector<std::string>> m_elements;
    int m_size;

public:

    explicit HashTable(int size)
        : m_elements(size), m_size(size)
    {

    }

    int size() const {return static_cast<int>(m_elements.size());}

    unsigned long long hashFunction(const std::string& str) const;

    void add(const std::string& str);

    void remove(const std::string& str);

    bool find(const std::string& str) const;

    std::vector<std::string>& check(int index);

    void processQuery(const std::string& query);


};

#endif //ALGORITHMS_HASH_TABLE_H
