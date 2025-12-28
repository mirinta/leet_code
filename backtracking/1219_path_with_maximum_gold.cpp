#include <vector>

/**
 * In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount
 * of gold in that cell, 0 if it is empty.
 *
 * Return the maximum amount of gold you can collect under the conditions:
 *
 * - Every time you are located in a cell you will collect all the gold in that cell.
 *
 * - From your position, you can walk one step to the left, right, up, or down.
 *
 * - You can't visit the same cell more than once.
 *
 * - Never visit a cell with 0 gold.
 *
 * - You can start and stop collecting gold from any position in the grid that has some gold.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 15
 * ! 0 <= grid[i][j] <= 100
 * ! There are at most 25 cells containing gold.
 */

class Solution {
public:
    int getMaximumGold(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result = std::max(result, backtrack(visited, i, j, grid));
            }
        }
        return result;
    }

private:
    int backtrack(std::vector<std::vector<bool>>& visited, int i, int j, const std::vector<std::vector<int>>& grid)
    {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return 0;

        if (visited[i][j] || grid[i][j] == 0)
            return 0;

        visited[i][j] = true;
        const int case1 = backtrack(visited, i + 1, j, grid);
        const int case2 = backtrack(visited, i - 1, j, grid);
        const int case3 = backtrack(visited, i, j + 1, grid);
        const int case4 = backtrack(visited, i, j - 1, grid);
        visited[i][j] = false;
        return grid[i][j] + std::max({case1, case2, case3, case4});
    }
};