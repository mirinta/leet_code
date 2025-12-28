#include <vector>

/**
 * You are given a 2D matrix grid of size m x n. You need to check if each cell grid[i][j] is:
 *
 * - Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
 *
 * - Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
 *
 * Return true if all the cells satisfy these conditions, otherwise, return false.
 *
 * ! 1 <= n, m <= 10
 * ! 0 <= grid[i][j] <= 9
 */

class Solution {
public:
    bool satisfiesConditions(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i + 1 < m && grid[i][j] != grid[i + 1][j])
                    return false;

                if (j + 1 < n && grid[i][j] == grid[i][j + 1])
                    return false;
            }
        }
        return true;
    }
};