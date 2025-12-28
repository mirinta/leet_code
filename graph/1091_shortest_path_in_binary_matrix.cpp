#include <queue>
#include <vector>

/**
 * Given an n x n binary matrix "grid", return the length of the shortest clear path in the matrix.
 * If there is no clear path, return -1.
 *
 * A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the
 * bottom-right cell (i.e., (n - 1, n - 1)) such that:
 *
 * - All the visited cells of the path are 0.
 *
 * - All the adjacent cells of the path are 8-directionally connected (i.e., they are different and
 * they share an edge or a corner).
 *
 * The length of a clear path is the number of visited cells of this path.
 *
 * ! n == grid.length
 * ! n == grid[i].length
 * ! 1 <= n <= 100
 * ! grid[i][j] is 0 or 1
 */

class Solution {
public:
    int shortestPathBinaryMatrix(const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
            return -1;

        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0},  {-1, 0},
                                                                  {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        visited[0][0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(0, 0);
        int length = 1;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (x == n - 1 && y == n - 1)
                    return length;

                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= n || j < 0 || j >= n)
                        continue;

                    if (!visited[i][j] && grid[i][j] == 0) {
                        visited[i][j] = true;
                        queue.emplace(i, j);
                    }
                }
            }
            length++;
        }
        return -1;
    }
};
