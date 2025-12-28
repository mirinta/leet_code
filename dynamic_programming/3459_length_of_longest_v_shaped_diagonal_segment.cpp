#include <functional>
#include <vector>

/**
 * You are given a 2D integer matrix grid of size n x m, where each element is either 0, 1, or 2.
 *
 * A V-shaped diagonal segment is defined as:
 *
 * - The segment starts with 1.
 *
 * - The subsequent elements follow this infinite sequence: 2, 0, 2, 0, ....
 *
 * - The segment:
 *
 *   - Starts along a diagonal direction (top-left to bottom-right, bottom-right to top-left,
 *     top-right to bottom-left, or bottom-left to top-right).
 *
 *   - Continues the sequence in the same diagonal direction.
 *
 *   - Makes at most one clockwise 90-degree turn to another diagonal direction while maintaining
 *     the sequence.
 *
 * Return the length of the longest V-shaped diagonal segment. If no valid segment exists, return 0.
 *
 * ! n == grid.length
 * ! m == grid[i].length
 * ! 1 <= n, m <= 500
 * ! grid[i][j] is either 0, 1 or 2.
 */

class Solution {
public:
    int lenOfVDiagonal(std::vector<std::vector<int>>& grid)
    {
        static const std::vector<std::pair<int, int>> directions{
            {-1, -1}, {-1, 1}, {1, 1}, {1, -1}}; // top-left, top-right, bottom-right, bottom-left
        const int m = grid.size();
        const int n = grid[0].size();
        int memo[500][500][4][2];
        std::memset(&memo, -1, sizeof(memo));
        std::function<int(int, int, int, bool, int)> dfs = [&](int x, int y, int d, bool canTurn, int target) {
            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != target)
                return 0;

            if (memo[x][y][d][canTurn] != -1)
                return memo[x][y][d][canTurn];

            int result = 1 + dfs(x + directions[d].first, y + directions[d].second, d, canTurn, 2 - target);
            if (canTurn) {
                const auto& [dx, dy] = directions[(d + 1) % 4];
                result = std::max(result, 1 + dfs(x + dx, y + dy, (d + 1) % 4, !canTurn, 2 - target));
            }
            return memo[x][y][d][canTurn] = result;
        };
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] != 1)
                    continue;

                for (int d = 0; d < directions.size(); ++d) {
                    const auto& [dx, dy] = directions[d];
                    result = std::max(result, 1 + dfs(i + dx, j + dy, d, true, 2));
                }
            }
        }
        return result;
    }
};