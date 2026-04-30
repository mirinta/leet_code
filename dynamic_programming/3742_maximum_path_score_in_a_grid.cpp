#include <vector>

/**
 * You are given an m x n grid where each cell contains one of the values 0, 1, or 2. You are also given an integer k.
 *
 * You start from the top-left corner (0, 0) and want to reach the bottom-right corner (m - 1, n - 1) by moving only
 * right or down.
 *
 * Each cell contributes a specific score an incurs an associated cost, according to their cell values:
 *
 * - 0: adds 0 to your score and costs 0.
 *
 * - 1: adds 1 to your score and costs 1.
 *
 * - 2: adds 1 to your score and costs 1.
 *
 * Return the maximum score achievable without exceeding a total cost of k, or -1 if no valid path exists.
 *
 * Note: If you reach the last cell but the total cost exceeds k, the path is invalid.
 *
 * ! 1 <= m, n <= 200
 * ! 0 <= k <= 10^3
 * ! grid[0][0] == 0
 * ! 0 <= grid[i][j] <= 2
 */

class Solution {
public:
    int maxPathScore(std::vector<std::vector<int>>& grid, int k)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        Memo memo(m, std::vector(n, std::vector(k + 1, -1)));
        return std::max(-1, dfs(memo, 0, 0, k, grid));
    }

private:
    using Memo = std::vector<std::vector<std::vector<int>>>;

    int dfs(Memo& memo, int i, int j, int remaining, const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (remaining < 0 || i < 0 || i >= m || j < 0 || j >= n)
            return INT_MIN;

        const int cost = std::clamp(grid[i][j], 0, 1);
        if (i == m - 1 && j == n - 1)
            return remaining >= cost ? grid[i][j] : INT_MIN;

        if (memo[i][j][remaining] != -1)
            return memo[i][j][remaining];

        const int case1 = dfs(memo, i, j + 1, remaining - cost, grid);
        const int case2 = dfs(memo, i + 1, j, remaining - cost, grid);
        int result = INT_MIN;
        if (case1 != INT_MIN) {
            result = std::max(result, grid[i][j] + case1);
        }
        if (case2 != INT_MIN) {
            result = std::max(result, grid[i][j] + case2);
        }
        return memo[i][j][remaining] = result;
    }
};