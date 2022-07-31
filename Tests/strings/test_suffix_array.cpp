//
// Created by daniel on 6/07/22.
//

#include "gtest/gtest.h"
#include "SuffixArray/count_sort.h"
#include "SuffixArray/suffix_array.h"


TEST(TestSuffixArray, ConstructSuffixArrayNaive)
{
    std::vector<int> expectedArray_1 {13, 5, 3, 1, 7, 9, 11, 6, 4, 2, 8, 10, 0, 12};
    ASSERT_EQ(expectedArray_1, suffixArrayNaive("panamabananas$"));

    std::vector<int> expectedArray_2 {3, 1, 2, 0};
    ASSERT_EQ(expectedArray_2, suffixArrayNaive("GAC$"));

    std::vector<int> expectedArray_3 {8, 7, 5, 3, 1, 6, 4, 2, 0};
    ASSERT_EQ(expectedArray_3, suffixArrayNaive("GAGAGAGA$"));

    std::vector<int> expectedArray_4 {15, 14, 0, 1, 12, 6, 4, 2, 8, 13, 3, 7, 9, 10, 11, 5};
    ASSERT_EQ(expectedArray_4, suffixArrayNaive("AACGATAGCGGTAGA$"));
}


TEST(TestSuffixArray, GetCharClasses)
{
    std::string text {"ababaa$"};
    std::vector<int> order {sortCharacters(text)};
    std::vector<int> classesExpected {1, 2, 1, 2, 1, 1, 0};
    ASSERT_EQ(classesExpected, getCharClasses(text, order));

    std::string text_1 {"AACGATAGCGGTAGA$"};
    std::vector<int> order_1 {15,0,1,4,6,12,14,2,8,3,7,9,10,13,5,11};
    std::vector<int> classesExpected_1 {1,1,2,3,1,4,1,3,2,3,3,4,1,3,1,0};
    ASSERT_EQ(classesExpected_1, getCharClasses(text_1, order_1));
}


TEST(TestSuffixArray, SortDoubledCyclifShifts)
{
    std::string text {"ababaa$"};
    std::vector<int> order {sortCharacters(text)};
    std::vector<int> classNumber {getCharClasses(text, order)};
    std::vector<int> orderExpected {6, 5, 4, 0, 2, 1, 3};
    ASSERT_EQ(orderExpected, sortDoubled(text, 1, order, classNumber));

    std::string text_1 {"AACGATAGCGGTAGA$"};
    std::vector<int> order_1 {15,0,1,4,6,12,14,2,8,3,7,9,10,13,5,11};
    std::vector<int> classes_1 {1,1,2,3,1,4,1,3,2,3,3,4,1,3,1,0};
    std::vector<int> orderExpected_1 {15,14,0,1,6,12,4,2,8,3,13,7,9,10,5,11};
    ASSERT_EQ(orderExpected_1, sortDoubled(text_1, 1, order_1, classes_1));

}

TEST(TestSuffixArray, UpdateClasses)
{
    std::vector<int> order {6, 5, 4, 0, 2, 1, 3};
    std::vector<int> classes {1, 2, 1, 2, 1, 1, 0};
    std::vector<int> classesUpdatedExpected {3, 4, 3, 4, 2, 1, 0};
    ASSERT_EQ(classesUpdatedExpected, updateClasses(order, classes, 1));

    std::vector<int> classes_1 {1,1,2,3,1,4,1,3,2,3,3,4,1,3,1,0};
    std::vector<int> order_1 {15,14,0,1,6,12,4,2,8,3,13,7,9,10,5,11};
    std::vector<int> classesExpected_1 {2,3,6,7,5,11,4,8,6,9,10,11,4,7,1,0};
    ASSERT_EQ(classesExpected_1, updateClasses(order_1, classes_1, 1));
}

TEST(TestSuffixArray, BuildSuffixArray)
{
    std::vector<int> expectedArray_1 {13, 5, 3, 1, 7, 9, 11, 6, 4, 2, 8, 10, 0, 12};
    ASSERT_EQ(expectedArray_1, suffixArray("panamabananas$"));

    std::vector<int> expectedArray_2 {3, 1, 2, 0};
    ASSERT_EQ(expectedArray_2, suffixArray("GAC$"));

    std::vector<int> expectedArray_3 {8, 7, 5, 3, 1, 6, 4, 2, 0};
    ASSERT_EQ(expectedArray_3, suffixArray("GAGAGAGA$"));

    std::vector<int> expectedArray_4 {15, 14, 0, 1, 12, 6, 4, 2, 8, 13, 3, 7, 9, 10, 11, 5};
    ASSERT_EQ(expectedArray_4, suffixArray("AACGATAGCGGTAGA$"));
}
