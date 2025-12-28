#include <vector>

/**
 * Given an integer "rowIndex", return the rowIndex-th (0-indexed) row of the Pascal's triangle.
 *
 * In Pascal's triangle, each number is the sum of the two numbers directly above it.
 *
 * ! 0 <= rowIndex <= 33
 */

class Solution {
public:
    std::vector<int> getRow(int rowIndex)
    {
        if (rowIndex < 0)
            return {};

        std::vector<int> prevRow(1, 1);
        for (int i = 1; i <= rowIndex; ++i) {
            std::vector<int> row(i + 1, 1);
            for (int j = 1; j < i; ++j) {
                row[j] = prevRow[j] + prevRow[j - 1];
            }
            prevRow = std::move(row);
        }
        return prevRow;
    }
};