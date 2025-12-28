#include <vector>

/**
 * Given a square matrix "mat", return the sum of the matrix diagonals.
 *
 * Only include the sum of all the elements on the primary diagonal and all the elements on the
 * secondary diagonal that are not part of the primary diagonal.
 */

class Solution {
public:
    int diagonalSum(std::vector<std::vector<int>>& mat)
    {
        const auto dimension = mat.size();
        int result = 0;
        for (size_t r = 0, i = 0, j = dimension - 1; r < dimension; ++r, ++i, --j) {
            result += i == j ? mat[r][i] : mat[r][i] + mat[r][j];
        }
        return result;
    }
};