#include <vector>

/**
 * You are given a 0-indexed matrix grid of order n * n. Each cell in this matrix has a value
 * grid[i][j], which is either a positive integer or -1 representing a blocked cell.
 *
 * You can move from a non-blocked cell to any non-blocked cell that shares an edge.
 *
 * For any cell (i, j), we represent its remoteness as R[i][j] which is defined as the following:
 *
 * - If the cell (i, j) is a non-blocked cell, R[i][j] is the sum of the values grid[x][y] such that
 * there is no path from the non-blocked cell (x, y) to the cell (i, j).
 *
 * - For blocked cells, R[i][j] == 0.
 *
 * Return the sum of R[i][j] over all cells.
 *
 * ! 1 <= n <= 300
 * !1 <= grid[i][j] <= 106 or grid[i][j] == -1
 */

class Solution {
public:
    long long sumRemoteness(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        long long totalSum = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == -1)
                    continue;

                totalSum += grid[i][j];
            }
        }
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == -1)
                    continue;

                long long count = 0;
                long long sum = 0;
                dfs(sum, count, grid, i, j);
                result += count * (totalSum - sum);
            }
        }
        return result;
    }

private:
    void dfs(long long& sum, long long& count, std::vector<std::vector<int>>& grid, int x, int y)
    {
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        sum += grid[x][y];
        count++;
        grid[x][y] = -1;
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == -1)
                continue;

            dfs(sum, count, grid, i, j);
        }
    }
};