#include <functional>
#include <string>
#include <vector>

/**
 * An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or
 * blank space ' '. These characters divide the square into contiguous regions.
 *
 * Given the grid grid represented as a string array, return the number of regions.
 *
 * Note that backslash characters are escaped, so a '\' is represented as '\\'.
 *
 * ! n == grid.length == grid[i].length
 * ! 1 <= n <= 30
 * ! grid[i][j] is either '/', '\', or ' '.
 */

class Solution {
public:
    int regionsBySlashes(std::vector<std::string>& grid)
    {
        // 0 1 1
        // 1 0 1 <= '\'
        // 1 1 0

        // 1 1 0
        // 1 0 1 <= '/'
        // 0 1 1

        // 1 1 1
        // 1 1 1 <= ' '
        // 1 1 1

        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> graph(3 * m, std::vector<int>(3 * n, 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == ' ')
                    continue;

                const int topLeftX = 3 * i;
                const int topLeftY = 3 * j;
                if (grid[i][j] == '/') {
                    graph[topLeftX][topLeftY + 2] = 0;
                    graph[topLeftX + 1][topLeftY + 1] = 0;
                    graph[topLeftX + 2][topLeftY] = 0;
                } else {
                    graph[topLeftX][topLeftY] = 0;
                    graph[topLeftX + 1][topLeftY + 1] = 0;
                    graph[topLeftX + 2][topLeftY + 2] = 0;
                }
            }
        }
        return numOfIslands(graph);
    }

private:
    int numOfIslands(const std::vector<std::vector<int>>& graph)
    {
        const int m = graph.size();
        const int n = graph[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        std::function<void(int, int)> dfs = [&](int i, int j) {
            if (i < 0 || i >= m || j < 0 || j >= n)
                return;

            if (graph[i][j] != 1 || visited[i][j])
                return;

            visited[i][j] = true;
            dfs(i + 1, j);
            dfs(i - 1, j);
            dfs(i, j + 1);
            dfs(i, j - 1);
        };
        int result = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][j] == 1 && !visited[i][j]) {
                    dfs(i, j);
                    result++;
                }
            }
        }
        return result;
    }
};