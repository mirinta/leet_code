#include <vector>

/**
 * You are given a 0-indexed 2D array grid of size 2 x n, where grid[r][c] represents the number of
 * points at position (r, c) on the matrix. Two robots are playing a game on this matrix.
 *
 * Both robots initially start at (0, 0) and want to reach (1, n-1). Each robot may only move to the
 * right ((r, c) to (r, c + 1)) or down ((r, c) to (r + 1, c)).
 *
 * At the start of the game, the first robot moves from (0, 0) to (1, n-1), collecting all the
 * points from the cells on its path. For all cells (r, c) traversed on the path, grid[r][c] is set
 * to 0. Then, the second robot moves from (0, 0) to (1, n-1), collecting the points on its path.
 * Note that their paths may intersect with one another.
 *
 * The first robot wants to minimize the number of points collected by the second robot. In
 * contrast, the second robot wants to maximize the number of points it collects. If both robots
 * play optimally, return the number of points collected by the second robot.
 *
 * ! grid.length == 2
 * ! n == grid[r].length
 * ! 1 <= n <= 5 * 10^4
 * ! 1 <= grid[r][c] <= 10^5
 */

class Solution {
public:
    long long gridGame(std::vector<std::vector<int>>& grid)
    {
        const int m = 2;
        const int n = grid[0].size();
        std::vector<std::vector<long long>> presum(m, std::vector<long long>(n + 1, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 1; j <= n; ++j) {
                presum[i][j] = presum[i][j - 1] + grid[i][j - 1];
            }
        }
        auto query = [&](int row, int l, int r) { return presum[row][r + 1] - presum[row][l]; };
        long long result = LLONG_MAX;
        for (int down = 0; down < n; ++down) {
            // path of robot1 = grid[0][0:down] -> grid[1][down:n-1]
            const long long score2 = std::max(query(0, down + 1, n - 1), query(1, 0, down - 1));
            result = std::min(result, score2);
        }
        return result;
    }
};