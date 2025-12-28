#include <cstddef>
#include <queue>
#include <vector>

/**
 * You are given an "n x n" binary matrix "grid" where 1 represents land and 0 represents water.
 *
 * An island is a 4-directionally connected group of 1's not connected to any other 1's. There are
 * exactly two islands in grid.
 *
 * You may change 0's to 1's to connect the two islands to form on island.
 *
 * Return the smallest number of 0's you must flip to connect the two islands.
 */

class Solution {
public:
    // DFS + BFS: time O(n^2), space O(n^2)
    int shortestBridge(std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        // step 1: DFS, mark one island with 2's and store coordinates of this island
        std::queue<std::pair<int, int>> queue;
        bool found = false;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dfs(queue, grid, i, j);
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
        // step 2: BFS, find the min distance between 2's and 1's
        int steps = 0;
        while (!queue.empty()) {
            const int size = queue.size();
            for (int k = 0; k < size; ++k) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] == 2)
                        continue;

                    if (grid[i][j] == 1)
                        return steps;

                    grid[i][j] = 2;
                    queue.emplace(i, j);
                }
            }
            steps++;
        }
        return steps;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

    void dfs(std::queue<std::pair<int, int>>& queue, std::vector<std::vector<int>>& grid, int x, int y)
    {
        queue.emplace(x, y);
        grid[x][y] = 2;
        const int n = grid.size();
        for (const auto& [dx, dy] : kDirections) {
            const int i = x + dx;
            const int j = y + dy;
            if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] != 1)
                continue;

            dfs(queue, grid, i, j);
        }
    }
};
