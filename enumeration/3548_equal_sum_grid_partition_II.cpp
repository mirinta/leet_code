#include <unordered_set>
#include <vector>

/**
 * You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either
 * one horizontal or one vertical cut on the grid such that:
 *
 * - Each of the two resulting sections formed by the cut is non-empty.
 *
 * - The sum of elements in both sections is equal, or can be made equal by discounting at most one single cell in total
 * (from either section).
 *
 * - If a cell is discounted, the rest of the section must remain connected.
 *
 * Return true if such a partition exists; otherwise, return false.
 *
 * Note: A section is connected if every cell in it can be reached from any other cell by moving up, down, left, or
 * right through other cells in the section.
 *
 * ! 1 <= m == grid.length <= 10^5
 * ! 1 <= n == grid[i].length <= 10^5
 * ! 2 <= m * n <= 10^5
 * ! 1 <= grid[i][j] <= 10^5
 */

class Solution {
public:
    bool canPartitionGrid(std::vector<std::vector<int>>& grid)
    {
        long long total = 0;
        for (const auto& row : grid) {
            for (const auto& val : row) {
                total += val;
            }
        }
        for (int k = 0; k < 4; ++k) {
            grid = rotate(grid);
            if (isValid(grid, total))
                return true;
        }
        return false;
    }

private:
    bool isValid(const std::vector<std::vector<int>>& grid, long long total)
    {
        // cut row the ith row, upper part = grid[0:i], lower part = grid[i+1:n-1]
        // check if we can apply operations on the upper part to make the grid valid
        // let S = sum of the upper part, S' = sum of the lower part
        // for any element x in the upper part,
        // we want S - x = S', and S' + S = total
        // then x = 2 * S - total
        const int m = grid.size();
        const int n = grid[0].size();
        long long S = 0;
        std::unordered_set<long long> set{0};
        for (int i = 0; i < m - 1; ++i) {
            for (int j = 0; j < n; ++j) {
                S += grid[i][j];
                if (i > 0 || j == 0 || j == n - 1) {
                    set.insert(grid[i][j]);
                }
            }
            const long long target = 2 * S - total;
            if (n == 1) {
                if (target == 0 || target == grid[0][0] || target == grid[i][0])
                    return true;

                continue;
            }
            if (set.count(target))
                return true;

            if (i == 0) {
                set.insert(grid[0].begin(), grid[0].end());
            }
        }
        return false;
    }

    // rotate 90 degrees (clockwise)
    std::vector<std::vector<int>> rotate(const std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> result(n, std::vector<int>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                result[j][m - i - 1] = grid[i][j];
            }
        }
        return result;
    }
};