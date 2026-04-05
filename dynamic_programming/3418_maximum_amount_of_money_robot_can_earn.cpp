#include <array>
#include <vector>

/**
 * You are given an m x n grid. A robot starts at the top-left corner of the grid (0, 0) and wants
 * to reach the bottom-right corner (m - 1, n - 1). The robot can move either right or down at any
 * point in time.
 *
 * The grid contains a value coins[i][j] in each cell:
 *
 * - If coins[i][j] >= 0, the robot gains that many coins.
 *
 * - If coins[i][j] < 0, the robot encounters a robber, and the robber steals the absolute value of
 * coins[i][j] coins.
 *
 * The robot has a special ability to neutralize robbers in at most 2 cells on its path, preventing
 * them from stealing coins in those cells.
 *
 * Note: The robot's total coins can be negative.
 *
 * Return the maximum profit the robot can gain on the route.
 *
 * ! m == coins.length
 * ! n == coins[i].length
 * ! 1 <= m, n <= 500
 * ! -1000 <= coins[i][j] <= 1000
 */

class Solution {
public:
    int maximumAmount(std::vector<std::vector<int>>& coins)
    {
        const int m = coins.size();
        const int n = coins[0].size();
        Memo memo(m, std::vector<std::array<int, 3>>(n, {INT_MIN, INT_MIN, INT_MIN}));
        return dfs(memo, 0, 0, 2, coins);
    }

private:
    using Memo = std::vector<std::vector<std::array<int, 3>>>;

    int dfs(Memo& memo, int i, int j, int ability, const std::vector<std::vector<int>>& coins)
    {
        if (i >= coins.size() || j >= coins[0].size())
            return INT_MIN;

        if (i == coins.size() - 1 && j == coins[0].size() - 1)
            return ability > 0 ? std::max(0, coins[i][j]) : coins[i][j];

        if (memo[i][j][ability] != INT_MIN)
            return memo[i][j][ability];

        int result = coins[i][j] + std::max(dfs(memo, i + 1, j, ability, coins), dfs(memo, i, j + 1, ability, coins));
        if (coins[i][j] < 0 && ability > 0) {
            result =
                std::max({result, dfs(memo, i + 1, j, ability - 1, coins), dfs(memo, i, j + 1, ability - 1, coins)});
        }
        return memo[i][j][ability] = result;
    }
};