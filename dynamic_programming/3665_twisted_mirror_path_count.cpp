#include <functional>
#include <vector>

/**
 * Given an m x n binary grid grid where:
 *
 * - grid[i][j] == 0 represents an empty cell, and
 *
 * - grid[i][j] == 1 represents a mirror.
 *
 * A robot starts at the top-left corner of the grid (0, 0) and wants to reach the bottom-right corner (m - 1, n - 1).
 * It can move only right or down. If the robot attempts to move into a mirror cell, it is reflected before entering
 * that cell:
 *
 * - If it tries to move right into a mirror, it is turned down and moved into the cell directly below the mirror.
 *
 * - If it tries to move down into a mirror, it is turned right and moved into the cell directly to the right of the
 * mirror. If this reflection would cause the robot to move outside the grid boundaries, the path is considered invalid
 * and should not be counted.
 *
 * Return the number of unique valid paths from (0, 0) to (m - 1, n - 1).
 *
 * Since the answer may be very large, return it modulo 10^9 + 7.
 *
 * Note: If a reflection moves the robot into a mirror cell, the robot is immediately reflected again based on the
 * direction it used to enter that mirror: if it entered while moving right, it will be turned down; if it entered while
 * moving down, it will be turned right. This process will continue until either the last cell is reached, the robot
 * moves out of bounds or the robot moves to a non-mirror cell.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 500
 * ! grid[i][j] is either 0 or 1.
 * ! grid[0][0] == grid[m - 1][n - 1] == 0
 */

class Solution {
public:
    int uniquePaths(std::vector<std::vector<int>>& grid)
    {
        static constexpr int kMod = 1e9 + 7;
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector memo(m, std::vector<std::array<int, 2>>(n, {-1, -1}));
        // dfs(x, y, d) = num of unique paths from (0,0) to (i,j) and
        //                the robot was moving d into (i,j)
        // d = 0 means down, d = 1 means right
        std::function<int(int, int, int)> dfs = [&](int x, int y, int d) {
            if (x >= m || x < 0 || y >= n || y < 0)
                return 0;

            if (x == m - 1 && y == n - 1)
                return 1;

            if (memo[x][y][d] != -1)
                return memo[x][y][d];

            if (grid[x][y] == 0)
                return memo[x][y][d] = (dfs(x + 1, y, 1) + dfs(x, y + 1, 0)) % kMod;

            return memo[x][y][d] = dfs(x + 1 - d, y + d, 1 - d);
        };
        return (dfs(0, 1, 0) + dfs(1, 0, 1)) % kMod;
    }
};
