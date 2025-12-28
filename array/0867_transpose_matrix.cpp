#include <vector>

/**
 * Given a 2D integer array matrix, return the transpose of matrix.
 *
 * The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's
 * row and column indices.
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 1000
 * ! 1 <= m * n <= 10^5
 * ! -10^9 <= matrix[i][j] <= 10^9
 */

class Solution {
public:
    std::vector<std::vector<int>> transpose(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<std::vector<int>> result(n, std::vector<int>(m, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[j][i] = matrix[i][j];
            }
        }
        return result;
    }
};