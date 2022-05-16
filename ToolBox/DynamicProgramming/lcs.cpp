//
// Created by daniel on 10/05/22.
//

#include "lcs.h"

std::string LCS(const std::string& str1, const std::string& str2)
{
    // Returns the longest common subsequence of a pair of strings.

    if (str1.length() == 0 || str2.length() == 0)
        return "";

    // Construct a table to store the length of the lcs of each subsequence
    // The value for the column 0 and row 0 should be zero
    int lenght_seq1 {static_cast<int>(str1.length())};
    int lenght_seq2 {static_cast<int>(str2.length())};
    sequence row(lenght_seq2 + 1, 0);
    std::vector<sequence> table(lenght_seq1 + 1, row);

    // Fill the table
    for (auto ii {1}; ii < lenght_seq1 + 1; ++ii)
    {
        for (auto jj {1}; jj < lenght_seq2 + 1; ++jj)
        {
            // If the elements of the two sequences match add 1 to the
            // diagonal element
            if (str1[ii - 1] == str2[jj - 1])
                table[ii][jj] = 1 + table[ii - 1][jj - 1];
                // Else compute the max of excluding the current element of one or the
                // other sequence
            else
                table[ii][jj] = std::max(table[ii][jj - 1], table[ii - 1][jj]);
        }
    }

    // Initialize the lcs string
    int lcs_lenght {table[lenght_seq1][lenght_seq2]};
    std::string lcs (lcs_lenght, 'a');

    // Traverse the table in reverse to construct the lcs
    int ii {lenght_seq1}; // row index
    int jj {lenght_seq2}; // column index
    int current_lenght {lcs_lenght};

    while (current_lenght != 0)
    {
        // move diagonally and include current character in the LCS if
        // the diagonal element is less than the current one and left, up
        // and diagonal elements are equal
        if (table[ii - 1][jj - 1] < current_lenght &&
            (table[ii - 1][jj - 1] == table[ii -1][jj] &&
             table[ii - 1][jj - 1]== table[ii][jj-1])
                )
        {
            current_lenght = table[ii - 1][jj - 1];
            lcs[current_lenght] = str1[ii - 1];
            --ii;
            --jj;
        }
            // Move up
        else if (table[ii][jj - 1] > table[ii - 1][jj])
        {
            current_lenght = table[ii][jj - 1];
            --jj;
        }
            // Move left
        else
        {
            current_lenght = table[ii - 1][jj];
            --ii;
        }
    }

    return lcs;
}

int LCSLength(const sequence &sequence_1, const sequence &sequence_2)
{
    // Returns the length of the longest common subsequence for a
    // pair of sequences of integers.

    // Construct a table to store the length of the lcs of each subsequence
    // The value for the column 0 and row 0 should be zero
    int lenght_seq1 {static_cast<int>(sequence_1.size())};
    int lenght_seq2 {static_cast<int>(sequence_2.size())};
    sequence row(lenght_seq2 + 1, 0);
    std::vector<sequence> table(lenght_seq1 + 1, row);

    // Fill the table
    for (auto ii {1}; ii < lenght_seq1 + 1; ++ii)
    {
        for (auto jj {1}; jj < lenght_seq2 + 1; ++jj)
        {
            // If the elements of the two sequences match add 1 to the
            // diagonal element
            if (sequence_1[ii - 1] == sequence_2[jj - 1])
                table[ii][jj] = 1 + table[ii - 1][jj - 1];
                // Else compute the max of excluding the current element of one or the
                // other sequence
            else
                table[ii][jj] = std::max(table[ii][jj - 1], table[ii - 1][jj]);
        }
    }

    return table[lenght_seq1][lenght_seq2];
}