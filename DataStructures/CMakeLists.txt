project(DataStructures)

set(HEADER_FILES
        Bst/SplayTree.h
        Bst/SearchTree.h
        Bst/AvlTree.h
        BinaryTree/BinaryTree.h
        LinkedList/linkedlist.h
        LinkedList/doublelist.h
        Stack/stack.h
        Tree/Tree.h
        Heap/heap.h
        Heap/heap_sort.h
        DisjointSets/disjoint_sets.h
        )

set(SOURCE_FILES
        Bst/SplayTree.cpp
        Bst/SearchTree.cpp
        Bst/AvlTree.cpp
        BinaryTree/BinaryTree.cpp
        LinkedList/linkedlist.cpp
        LinkedList/doublelist.cpp
        Stack/stack.cpp
        Tree/Tree.cpp
        Heap/heap.cpp
        DisjointSets/disjoint_sets.cpp
        )

add_library(DataStructures STATIC ${SOURCE_FILES} ${HEADER_FILES})