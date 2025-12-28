#include <vector>

/**
 * Given a m x n matrix mat and an integer k, return a matrix answer where each answer[i][j] is the
 * sum of all elements mat[r][c] for:
 *
 * - i - k <= r <= i + k,
 *
 * - j - k <= c <= j + k, and
 *
 * - (r, c) is a valid position in the matrix.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n, k <= 100
 * ! 1 <= mat[i][j] <= 100
 */

class Solution {
public:
    std::vector<std::vector<int>> matrixBlockSum(std::vector<std::vector<int>>& mat, int k)
    {
        // presum[i][j] = sum of all elements of the submatrix mat[0:i-1][0:j-1]
        const int m = mat.size();
        const int n = mat[0].size();
        std::vector<std::vector<int>> presum(m + 1, std::vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
        std::vector<std::vector<int>> result(m, std::vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const int x1 = std::max(0, i - k);
                const int y1 = std::max(0, j - k);
                const int x2 = std::min(m - 1, i + k);
                const int y2 = std::min(n - 1, j + k);
                result[i][j] = query(x1, y1, x2, y2, presum);
            }
        }
        return result;
    }

private:
    int query(int x1, int y1, int x2, int y2, const std::vector<std::vector<int>>& presum)
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }
};