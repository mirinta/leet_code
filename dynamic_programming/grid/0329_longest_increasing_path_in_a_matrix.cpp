#include <vector>

/**
 * Given an m x n integers matrix, return the length of the longest increasing path in matrix.
 *
 * From each cell, you can either move in four directions: left, right, up, or down. You may not
 * move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
 *
 * ! m == matrix.length
 * ! n == matrix[i].length
 * ! 1 <= m, n <= 200
 * ! 0 <= matrix[i][j] <= 2^31 - 1
 */

class Solution {
public:
    int longestIncreasingPath(std::vector<std::vector<int>>& matrix)
    {
        const int m = matrix.size();
        const int n = matrix[0].size();
        std::vector<std::vector<int>> memo(m, std::vector<int>(n, -1));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = std::max(result, dp(memo, i, j, matrix));
            }
        }
        return result;
    }

private:
    // length of the longest increasing path starting from (i,j)
    int dp(std::vector<std::vector<int>>& memo, int i, int j, const std::vector<std::vector<int>>& matrix)
    {
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        if (memo[i][j] != -1)
            return memo[i][j];

        int result = 1; // matrix[i][j] is taken into account
        for (const auto& [dx, dy] : kDirections) {
            const int x = i + dx;
            const int y = j + dy;
            if (x < 0 || x >= matrix.size() || y < 0 || y >= matrix[0].size())
                continue;

            if (matrix[i][j] < matrix[x][y]) {
                result = std::max(result, 1 + dp(memo, x, y, matrix));
            }
        }
        return memo[i][j] = result;
    }
};