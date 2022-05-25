//
// Created by daniel on 25/05/22.
//

#ifndef ALGORITHMS_DISJOINT_SETS_H
#define ALGORITHMS_DISJOINT_SETS_H

#endif //ALGORITHMS_DISJOINT_SETS_H


#include <vector>

class DisjointSets
{
    // Disjoint sets data structure using trees
private:
    std::vector<int> m_parent;
    std::vector<int> m_rank;
    bool m_pathCompression;

    int _find(int element);

    int _find_path_compression(int element);

public:

    explicit DisjointSets(int size, bool path_compression=false)
        : m_parent(size), m_rank(size), m_pathCompression(path_compression)
    {

    }

    DisjointSets(std::vector<int> parent, std::vector<int> rank, bool path_compression=false)
        : m_parent(std::move(parent)), m_rank(std::move(rank)), m_pathCompression(path_compression)
    {

    }

    int parentSize() const {return static_cast<int>(m_parent.size());}

    int ranKSize() const {return static_cast<int>(m_rank.size());}

    bool pathCompression() const {return m_pathCompression;}

    // Returns a copy of the m_parent vector
    std::vector<int> getParent() {return m_parent;}
    // Returns a copy of the m_rank vector
    std::vector<int> getRank() {return m_rank;}

    void makeSet(int element);

    void setUnion(int element_1, int element_2);

    int find(int element);

};