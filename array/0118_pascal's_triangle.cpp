#include <vector>

/**
 * Given an integer "numRows", return the first numRows of Pascal's triangle.
 *
 * In Pascal's triangle, each number is the sum of the two number directly above it.
 *
 * ! 1 <= numRows <= 30
 */

class Solution {
public:
    std::vector<std::vector<int>> generate(int numRows)
    {
        // row1: 1
        // row2: 1 1
        // row3: 1 2 1
        // row4: 1 3 3 1
        // num of elements of ith row = i (1-indexed)
        std::vector<std::vector<int>> result(numRows);
        for (int i = 1; i <= numRows; ++i) {
            result[i - 1] = std::vector<int>(i, 1);
            for (int j = 1; j < i - 1; ++j) {
                result[i - 1][j] = result[i - 2][j - 1] + result[i - 2][j];
            }
        }
        return result;
    }
};
