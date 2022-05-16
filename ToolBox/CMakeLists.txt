project(ToolBox)

set(HEADER_FILES
        Divide&Conquer/BinarySearch.h
        Divide&Conquer/MergeSort.h
        Divide&Conquer/ClosestPoints.h
        Divide&Conquer/Quicksort.h
        Divide&Conquer/Inversions.h
        Divide&Conquer/knapsack.h
        Divide&Conquer/MajorityElement.h
        Divide&Conquer/Segments.h
        Greedy/Change.h
        Greedy/Refills.h
        Greedy/maxRevenue.h
        DynamicProgramming/Knapsack.h
        DynamicProgramming/SubsetCounter.h
        DynamicProgramming/editDistance.h
        DynamicProgramming/coins.h
        DynamicProgramming/lcs.h
        DynamicProgramming/MaxValue.h
        )

set(SOURCE_FILES
        Divide&Conquer/BinarySearch.cpp
        Divide&Conquer/MergeSort.cpp
        Divide&Conquer/ClosestPoints.cpp
        Divide&Conquer/Quicksort.cpp
        Divide&Conquer/Inversions.cpp
        Divide&Conquer/knapsack.cpp
        Divide&Conquer/MajorityElement.cpp
        Divide&Conquer/Segments.cpp
        Greedy/Change.cpp
        Greedy/Refills.cpp
        Greedy/maxRevenue.cpp
        DynamicProgramming/Knapsack.cpp
        DynamicProgramming/SubsetCounter.cpp
        DynamicProgramming/editDistance.cpp
        DynamicProgramming/coins.cpp
        DynamicProgramming/lcs.cpp
        DynamicProgramming/MaxValue.cpp
        )

add_library(ToolBox STATIC ${SOURCE_FILES} ${HEADER_FILES})