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
        )

add_library(DataStructures STATIC ${SOURCE_FILES} ${HEADER_FILES})