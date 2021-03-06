//
// Created by daniel on 29/06/22.
//

#include "gtest/gtest.h"
#include "BurrowsWheeler/burrows_wheeler.h"


TEST(BurrowWheelers, ConstructBWMatrix)
{

    BurrowsWheeler bw_1("AA$");
    std::vector<std::string> expected_matrix_1 {
            "$AA",
            "A$A",
            "AA$",
    };
    ASSERT_EQ(bw_1.matrix(), expected_matrix_1);

    BurrowsWheeler bw_2("ACACACAC$");
    std::vector<std::string> expected_matrix_2 {
             "$ACACACAC",
             "AC$ACACAC",
             "ACAC$ACAC",
             "ACACAC$AC",
             "ACACACAC$",
             "C$ACACACA",
             "CAC$ACACA",
             "CACAC$ACA",
             "CACACAC$A",
    };
    ASSERT_EQ(bw_2.matrix(), expected_matrix_2);
}


TEST(BurrowWheelers, GetTransformFromMatrix)
{
    BurrowsWheeler bw_1("AA$");
    ASSERT_EQ(bw_1.getTransform(), "AA$");

    BurrowsWheeler bw_2("ACACACAC$");
    ASSERT_EQ(bw_2.getTransform(), "CCCC$AAAA");

    BurrowsWheeler bw_3("AGACATA$");
    ASSERT_EQ(bw_3.getTransform(), "ATG$CAAA");

    BurrowsWheeler bw_4("panamabananas$");
    ASSERT_EQ(bw_4.getTransform(), "smnpbnnaaaaa$a");

    BurrowsWheeler bw_5("banana$");
    ASSERT_EQ(bw_5.getTransform(), "annb$aa");
}


TEST(BurrowsWheeler, FirstAndLastColumn)
{
    BurrowsWheeler bw ("panamabananas$");
    std::array<std::string , 2> columns_actual {bw.firstAndLastColumn()};
    std::array<std::string , 2> columns_expected {
        "$aaaaaabmnnnps",
        "smnpbnnaaaaa$a",
    };

    ASSERT_EQ(columns_actual[0].size(), 14);
    ASSERT_EQ(columns_expected, columns_actual);
}


TEST(BurrowWheelers, SortedPositionsArray)
{
    std::vector<int> positionsExpected {13, 8, 9, 12, 7, 10, 11, 1, 2, 3, 4, 5, 0, 6};
    std::vector<int> positionsActual {InverseBW::sortedPositions("smnpbnnaaaaa$a")};

    ASSERT_EQ(positionsExpected, positionsActual);
}


TEST(BurrowWheelers, InverseBWTransform)
{
    InverseBW transform_1 ("AC$A");
    ASSERT_EQ(transform_1.inverse(), "ACA$");

    InverseBW transform_2 ("AGGGAA$");
    ASSERT_EQ(transform_2.inverse(), "GAGAGA$");

    InverseBW transform_3 ("smnpbnnaaaaa$a");
    ASSERT_EQ(transform_3.inverse(), "panamabananas$");

    InverseBW transform_4 ("annb$aa");
    ASSERT_EQ(transform_4.inverse(), "banana$");
}


TEST(BurrowsWheelers, MatchEmptyPattern)
{
    BurrowsWheeler bw_1 {"panamabananas$"};
    ASSERT_EQ(bw_1.patternCount(""), 0);
}


TEST(BurrowsWheelers, PatternMatching)
{
    BurrowsWheeler bw_1 {"panamabananas$"};
    ASSERT_EQ(bw_1.patternCount("ana"), 3);

    BurrowsWheeler bw_2 {"GAGAGA$"};
    ASSERT_EQ(bw_2.patternCount("GA"), 3);

    BurrowsWheeler bw_3 {"AGGGAA$"};
    ASSERT_EQ(bw_2.patternCount("CT"), 0);
}


TEST(BurrowsWheelers, CountMap)
{
    std::map<char, std::vector<int>> expectedCount {
            {'$', {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}},
            {'a', {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 5, 6}},
            {'b', {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
            {'m', {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
            {'n', {0, 0, 0, 1, 1, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3}},
            {'p', {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
            {'s', {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}
    };
    std::map<char, std::vector<int>> actualCount {BurrowsWheeler::countMap("smnpbnnaaaaa$a")};

    ASSERT_EQ(expectedCount, actualCount);
}


TEST(BurrowsWheelers, firstOccurence)
{
    std::map<char, int> expectedOccurrence {
            {'$', 0},
            {'a', 1},
            {'b', 7},
            {'m', 8},
            {'n', 9},
            {'p', 12},
            {'s', 13}
    };

    std::map<char, int> actualOccurrences {BurrowsWheeler::firstOccurrence("$aaaaaabmnnnps")};
    ASSERT_EQ(expectedOccurrence, actualOccurrences);
}


TEST(BurrowsWheelers, BetterPatternMatching)
{
    BurrowsWheeler bw_1 {"panamabananas$"};
    ASSERT_EQ(bw_1.betterPatternCount("ana"), 3);

    BurrowsWheeler bw_2 {"GAGAGA$"};
    ASSERT_EQ(bw_2.betterPatternCount("GA"), 3);

    BurrowsWheeler bw_3 {"AGGGAA$"};
    ASSERT_EQ(bw_3.betterPatternCount("CT"), 0);
}

