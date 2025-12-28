#include <vector>

/**
 * You are given an m x n 2D array grid of positive integers.
 *
 * Your task is to traverse grid in a zigzag pattern while skipping every alternate cell.
 *
 * Zigzag pattern traversal is defined as following the below actions:
 *
 * - Start at the top-left cell (0, 0).
 *
 * - Move right within a row until the end of the row is reached.
 *
 * - Drop down to the next row, then traverse left until the beginning of the row is reached.
 *
 * - Continue alternating between right and left traversal until every row has been traversed.
 *
 * Note that you must skip every alternate cell during the traversal.
 *
 * Return an array of integers result containing, in order, the value of the cells visited during
 * the zigzag traversal with skips.
 *
 * ! 2 <= n == grid.length <= 50
 * ! 2 <= m == grid[i].length <= 50
 * ! 1 <= grid[i][j] <= 2500
 */

class Solution {
public:
    std::vector<int> zigzagTraversal(std::vector<std::vector<int>>& grid)
    {
        const int n = grid[0].size();
        bool skip = false;
        bool toRight = true;
        std::vector<int> result;
        for (const auto& row : grid) {
            for (int i = toRight ? 0 : n - 1; toRight ? i < n : i >= 0; toRight ? ++i : --i) {
                if (!skip) {
                    result.push_back(row[i]);
                }
                skip = !skip;
            }
            toRight = !toRight;
        }
        return result;
    }
};