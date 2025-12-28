#include <queue>
#include <vector>

/**
 * You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell
 * has one of three values:
 *
 * - 0 represents grass,
 *
 * - 1 represents fire,
 *
 * - 2 represents a wall that you and fire cannot pass through.
 *
 * You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the
 * bottom-right cell, (m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After
 * your move, every fire cell will spread to all adjacent cells that are not walls.
 *
 * Return the maximum number of minutes that you can stay in your initial position before moving
 * while still safely reaching the safehouse. If this is impossible, return -1. If you can always
 * reach the safehouse regardless of the minutes stayed, return 109.
 *
 * Note that even if the fire spreads to the safehouse immediately after you have reached it, it
 * will be counted as safely reaching the safehouse.
 *
 * A cell is adjacent to another cell if the former is directly north, east, south, or west of the
 * latter (i.e., their sides are touching).
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 300
 * ! 4 <= m * n <= 2 * 10^4
 * ! grid[i][j] is either 0, 1, or 2.
 * ! grid[0][0] == grid[m - 1][n - 1] == 0
 */

class Solution {
public:
    int maximumMinutes(std::vector<std::vector<int>>& grid)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        std::queue<std::pair<int, int>> fire;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    fire.emplace(i, j);
                }
            }
        }
        int min = 0;
        int max = 1e9;
        while (min <= max) {
            const int time = min + (max - min) / 2;
            if (isValid(fire, grid, time, m, n)) {
                min = time + 1;
            } else {
                max = time - 1;
            }
        }
        return max;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    bool isValid(std::queue<std::pair<int, int>> fire, std::vector<std::vector<int>> grid, int time, int m, int n)
    {
        spreadFire(fire, grid, time, m, n);
        std::queue<std::pair<int, int>> queue;
        queue.emplace(0, 0);
        grid[0][0] = 3;
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (grid[x][y] == 1)
                    continue;

                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] != 0)
                        continue;

                    if (i == m - 1 && j == n - 1)
                        return true;

                    grid[i][j] = 3;
                    queue.emplace(i, j);
                }
            }
            spreadFire(fire, grid, 1, m, n);
        }
        return false;
    }

    void spreadFire(std::queue<std::pair<int, int>>& fire, std::vector<std::vector<int>>& grid, int time, int m, int n)
    {
        while (!fire.empty() && time > 0) {
            for (int k = fire.size(); k > 0; --k) {
                const auto [x, y] = fire.front();
                fire.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (grid[i][j] != 1 && grid[i][j] != 2) {
                        grid[i][j] = 1;
                        fire.emplace(i, j);
                    }
                }
            }
            time--;
        }
    }
};