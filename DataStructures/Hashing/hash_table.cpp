//
// Created by daniel on 26/05/22.
//

#include "hash_table.h"
#include <iostream>

unsigned long long HashTable::hashFunction(const std::string &str) const
{
    // Returns the hash of a string
    unsigned long long hash {0};
    int size {static_cast<int>(str.size() - 1)};

    for (int ii {size}; ii >= 0; --ii)
        hash = (hash * multiplier + str[ii]) % prime;
    return hash % m_size;
}

void HashTable::add(const std::string &str)
{
    // Add a string to the hash table
    if (!find(str))
    {
        std::vector<std::string>& chain {m_elements[hashFunction(str)]};
        chain.insert(chain.begin(), str);
    }
}

void HashTable::remove(const std::string &str)
{
    // Remove a string from the hash table
    std::vector<std::string>& chain {m_elements[hashFunction(str)]};
    int ii {0};
    for (const auto& element : chain)
    {
        if (element == str)
        {
            chain.erase(chain.begin() + ii);
            break;
        }
        ++ii;
    }
}

bool HashTable::find(const std::string &str) const
{
    // Finds a string in the hash table
    unsigned long long chain {hashFunction(str)};

    if (std::any_of(m_elements[chain].begin(), m_elements[chain].end(),
                    [&str](const std::string& other) {return str == other;}))
        return true;
    return false;
}

std::vector<std::string> &HashTable::check(int index)
{
    // Returns a chain from the hash table
    return m_elements[index];
}

void HashTable::processQuery(const std::string &query)
{
    // Process a query. Valid queries are 'add string', 'del string',
    // 'find string' and 'check chain number'.

    // Get the type of the query
    std::size_t spacePos {query.find(' ')};
    std::string queryType {query.substr(0, spacePos)};

    if (queryType == "add")
        add(query.substr(spacePos + 1));
    else if (queryType == "del")
        remove(query.substr(spacePos + 1));
    else if (queryType == "find")
        find(query.substr(spacePos + 1));
    else if (queryType == "check")
    {
        int index {std::stoi(query.substr(spacePos + 1))};
        check(index);
    }
}
