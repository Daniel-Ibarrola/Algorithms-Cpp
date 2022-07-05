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


TEST(BurrowWheelers, SortedPositionsArray)
{
    std::vector<int> positionsExpected {13, 8, 9, 12, 7, 10, 11, 1, 2, 3, 4, 5, 0, 6};
    InverseBW transform {"smnpbnnaaaaa$a"};
    std::vector<int> positionsActual {transform.sortedPositions()};

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
