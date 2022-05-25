//
// Created by daniel on 25/05/22.
//

#include "disjoint_sets.h"

int DisjointSets::_find(int element)
{
    // Returns the root of the tree which the given element belongs
    while (m_parent[element] != element)
        element = m_parent[element];
    return element;
}

int DisjointSets::_find_path_compression(int element)
{
    // Returns the root of the tree which the given element belongs and applies
    // path compression
    if(m_parent[element] != element)
        m_parent[element] = _find_path_compression(m_parent[element]);

    return m_parent[element];
}

void DisjointSets::makeSet(int element)
{
    // Create a set with the given element
    m_parent[element] = element;
    m_rank[element] = 0;
}

void DisjointSets::setUnion(int element_1, int element_2)
{
    // Union of two sets. Joins the trees each element belongs to on the
    // union by rank heuristic

    int root_1 {find(element_1)};
    int root_2 {find(element_2)};
    // If both sets are equal we do nothing
    if (root_1 == root_2)
        return;

    // Join the root with lower rank to the root with higher rank
    if (m_rank[root_1] > m_rank[root_2])
        m_parent[root_2] = root_1;
    else
    {
        m_parent[root_1] = root_2;
        // If the ranks are equal they need to be updated
        if (m_rank[root_1] == m_rank[root_2])
            m_rank[root_2]++;
    }
}

int DisjointSets::find(int element)
{
    // Find the set which the given element belongs
    if (pathCompression())
        return _find_path_compression(element);
    return _find(element);
}
