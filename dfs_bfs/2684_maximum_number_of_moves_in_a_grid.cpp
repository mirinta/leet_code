#include <queue>
#include <vector>

/**
 * You are given a 0-indexed m x n matrix grid consisting of positive integers.
 *
 * You can start at any cell in the first column of the matrix, and traverse the grid in the
 * following way:
 *
 * From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and
 * (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than
 * the value of the current cell. Return the maximum number of moves that you can perform.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 1000
 * ! 4 <= m * n <= 10^5
 * ! 1 <= grid[i][j] <= 10^6
 */

class Solution {
public:
    int maxMoves(std::vector<std::vector<int>>& grid)
    {
        return approach3(grid);
    }

private:
    // BFS, TC = O(MN), SC = O(MN)
    int approach3(const std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> kDirections{{-1, 1}, {0, 1}, {1, 1}};
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; ++i) {
            visited[i][0] = true;
            queue.emplace(i, 0);
        }
        int result = -1;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (!visited[i][j] && grid[x][y] < grid[i][j]) {
                        visited[i][j] = true;
                        queue.emplace(i, j);
                    }
                }
            }
            result++;
        }
        return result;
    }

    // DP with space optimization, TC = O(MN), SC = O(M)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<int> dp(m, 0);
        auto prev = dp;
        int result = 0;
        for (int j = 1; j < n; ++j) {
            prev.assign(dp.begin(), dp.end());
            std::fill(dp.begin(), dp.end(), INT_MIN);
            for (int i = 0; i < m; ++i) {
                if (i > 0 && grid[i][j] > grid[i - 1][j - 1]) {
                    dp[i] = std::max(dp[i], 1 + prev[i - 1]);
                }
                if (grid[i][j] > grid[i][j - 1]) {
                    dp[i] = std::max(dp[i], 1 + prev[i]);
                }
                if (i + 1 < m && grid[i][j] > grid[i + 1][j - 1]) {
                    dp[i] = std::max(dp[i], 1 + prev[i + 1]);
                }
                result = std::max(result, dp[i]);
            }
        }
        return result;
    }

    // DP, TC = O(MN), SC = O(MN)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        // dp[j][i] = max num of moves from the first column to grid[i][j]
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> dp(n, std::vector<int>(m, INT_MIN));
        for (int i = 0; i < m; ++i) {
            dp[0][i] = 0;
        }
        int result = 0;
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < m; ++i) {
                if (i > 0 && grid[i][j] > grid[i - 1][j - 1]) {
                    dp[j][i] = std::max(dp[j][i], 1 + dp[j - 1][i - 1]);
                }
                if (grid[i][j] > grid[i][j - 1]) {
                    dp[j][i] = std::max(dp[j][i], 1 + dp[j - 1][i]);
                }
                if (i + 1 < m && grid[i][j] > grid[i + 1][j - 1]) {
                    dp[j][i] = std::max(dp[j][i], 1 + dp[j - 1][i + 1]);
                }
                result = std::max(result, dp[j][i]);
            }
        }
        return result;
    }
};