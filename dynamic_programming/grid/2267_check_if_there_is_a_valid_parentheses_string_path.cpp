#include <vector>

/**
 * A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of
 * the following conditions is true:
 *
 * - It is ().
 *
 * - It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
 *
 * - It can be written as (A), where A is a valid parentheses string.
 *
 * You are given an m x n matrix of parentheses grid. A valid parentheses string path in the grid is
 * a path satisfying all of the following conditions:
 *
 * - The path starts from the upper left cell (0, 0).
 *
 * - The path ends at the bottom-right cell (m - 1, n - 1).
 *
 * - The path only ever moves down or right.
 *
 * - The resulting parentheses string formed by the path is valid.
 *
 * Return true if there exists a valid parentheses string path in the grid. Otherwise, return false.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 100
 * ! grid[i][j] is either '(' or ')'.
 */

class Solution {
public:
    bool hasValidPath(std::vector<std::vector<char>>& grid)
    {
        // length of any path from (0,0) to (m-1,n-1) = m+n-1
        // thus, num of '(' = num of ')' = (m+n-1)/2
        const int m = grid.size();
        const int n = grid[0].size();
        if (grid[0][0] != '(' || grid[m - 1][n - 1] != ')' || (m + n - 1) % 2 != 0)
            return false;

        const int target = (m + n - 1) / 2;
        std::vector<std::vector<std::vector<int>>> memo(
            m, std::vector<std::vector<int>>(n, std::vector<int>(target + 1, -1)));
        return dfs(memo, 0, 0, 0, grid);
    }

private:
    // balance = num of '(' - num of ')'
    bool dfs(std::vector<std::vector<std::vector<int>>>& memo,
             int i,
             int j,
             int balance,
             const std::vector<std::vector<char>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n)
            return false;

        if (balance < 0)
            return false;

        if (m - i + n - j - 1 < balance)
            return false;

        if (i == m - 1 && j == n - 1)
            return grid[i][j] == ')' && balance == 1;

        if (memo[i][j][balance] != -1)
            return memo[i][j][balance];

        const int offset = grid[i][j] == ')' ? -1 : 1;
        return memo[i][j][balance] =
                   dfs(memo, i + 1, j, balance + offset, grid) || dfs(memo, i, j + 1, balance + offset, grid);
    }
};