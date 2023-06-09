#include <queue>
#include <vector>

/**
 * Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
 *
 * The distance between two adjacent cells is 1.
 *
 * ! m == mat.length
 * ! n == mat[i].length
 * ! 1 <= m, n <= 10^4
 * ! 1 <= m * n <= 10^4
 * ! mat[i][j] is either 0 or 1.
 * ! There is at least one 0 in mat.
 */

class Solution
{
public:
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat)
    {
        const int m = mat.size();
        const int n = mat[0].size();
        std::queue<std::pair<int, int>> queue;
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    queue.push({i, j});
                    visited[i][j] = true;
                }
            }
        }
        while (!queue.empty()) {
            const auto [x, y] = queue.front();
            queue.pop();
            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j])
                    continue;

                queue.push({i, j});
                mat[i][j] = mat[x][y] + 1;
                visited[i][j] = true;
            }
        }
        return mat;
    }
};