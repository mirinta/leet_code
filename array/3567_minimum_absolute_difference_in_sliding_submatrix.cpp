#include <algorithm>
#include <climits>
#include <vector>

/**
 * You are given an m x n integer matrix grid and an integer k.
 *
 * For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values
 * within that submatrix.
 *
 * Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the
 * submatrix whose top-left corner is (i, j) in grid.
 *
 * Note: If all elements in the submatrix have the same value, the answer will be 0.
 *
 * A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1
 * <= y <= y2.
 *
 * ! 1 <= m == grid.length <= 30
 * ! 1 <= n == grid[i].length <= 30
 * ! -10^5 <= grid[i][j] <= 10^5
 * ! 1 <= k <= min(m, n)
 */

class Solution {
public:
    std::vector<std::vector<int>> minAbsDiff(std::vector<std::vector<int>>& grid, int k)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> result(m - k + 1, std::vector<int>(n - k + 1, INT_MAX));
        for (int i = 0; i + k - 1 < m; ++i) {
            for (int j = 0; j + k - 1 < n; ++j) {
                std::vector<int> data;
                for (int p = 0; p < k; ++p) {
                    for (int q = 0; q < k; ++q) {
                        data.push_back(grid[i + p][j + q]);
                    }
                }
                if (data.size() == 1) {
                    result[i][j] = 0;
                    continue;
                }
                std::sort(data.begin(), data.end());
                for (int r = 1; r < data.size(); ++r) {
                    if (data[r] == data[r - 1])
                        continue;

                    result[i][j] = std::min(result[i][j], data[r] - data[r - 1]);
                }
                if (result[i][j] == INT_MAX) {
                    result[i][j] = 0;
                }
            }
        }
        return result;
    }
};
