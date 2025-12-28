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

class Solution {
public:
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>>& mat)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int m = mat.size();
        const int n = mat[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 0) {
                    queue.emplace(i, j);
                    visited[i][j] = true;
                }
            }
        }
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j])
                        continue;

                    visited[i][j] = true;
                    mat[i][j] = mat[x][y] + 1;
                    queue.emplace(i, j);
                }
            }
        }
        return mat;
    }
};
