#include <vector>

/**
 * You are given a 0-indexed integer matrix grid and an integer k.
 *
 * Return the number of submatrices that contain the top-left element of the grid, and have a sum
 * less than or equal to k.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= n, m <= 1000
 * ! 0 <= grid[i][j] <= 1000
 * ! 1 <= k <= 10^9
 */

class PrefixSum2D {
public:
    explicit PrefixSum2D(const std::vector<std::vector<int>>& mat)
        : presum(mat.size() + 1, std::vector<int>(mat[0].size() + 1, 0))
    {
        for (int i = 1; i <= mat.size(); ++i) {
            for (int j = 1; j <= mat[0].size(); ++j) {
                presum[i][j] = presum[i - 1][j] + presum[i][j - 1] - presum[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }
    }

    int query(int x1, int y1, int x2, int y2)
    {
        return presum[x2 + 1][y2 + 1] - presum[x2 + 1][y1] - presum[x1][y2 + 1] + presum[x1][y1];
    }

private:
    std::vector<std::vector<int>> presum;
};

class Solution {
public:
    int countSubmatrices(std::vector<std::vector<int>>& grid, int k)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        PrefixSum2D presum2D(grid);
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (presum2D.query(0, 0, i, j) <= k) {
                    result++;
                }
            }
        }
        return result;
    }
};