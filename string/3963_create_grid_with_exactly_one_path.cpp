#include <string>
#include <vector>

/**
 * You are given two integers m and n, representing the number of rows and columns of a grid.
 *
 * Construct any m x n grid consisting only of the characters '.' and '#', where:
 *
 * - '.' represents a free cell.
 *
 * - '#' represents an obstacle cell.
 *
 * A valid path is a sequence of free cells that:
 *
 * - Starts at the top-left cell (0, 0).
 *
 * - Ends at the bottom-right cell (m - 1, n - 1).
 *
 * - Moves only:
 *     - Right, from (i, j) to (i, j + 1), or
 *     - Down, from (i, j) to (i + 1, j).
 *
 * Return any grid such that there is exactly one valid path from the top-left cell to the bottom-right cell.
 *
 * ! 1 <= m, n <= 25
 */

class Solution {
public:
    std::vector<std::string> createGrid(int m, int n)
    {
        std::vector<std::string> result;
        result.reserve(m);
        result.emplace_back(n, '.');
        for (int i = 1; i < m; ++i) {
            result.emplace_back(n, '#');
            result[i].back() = '.';
        }
        return result;
    }
};
