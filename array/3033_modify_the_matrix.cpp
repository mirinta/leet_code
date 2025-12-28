#include <vector>

/**
 * Given a 0-indexed m x n integer matrix matrix, create a new 0-indexed matrix called answer. Make
 * answer equal to matrix, then replace each element with the value -1 with the maximum element in
 * its respective column.
 *
 * Return the matrix answer.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 2 <= m, n <= 50
 * ! -1 <= matrix[i][j] <= 100
 * ! The input is generated such that each column contains at least one non-negative integer.
 */

class Solution {
public:
    std::vector<std::vector<int>> modifiedMatrix(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<int> max(n, INT_MIN);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                max[j] = std::max(max[j], matrix[i][j]);
            }
        }
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == -1) {
                    result[i][j] = max[j];
                } else {
                    result[i][j] = matrix[i][j];
                }
            }
        }
        return result;
    }
};