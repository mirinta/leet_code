#include <array>
#include <queue>
#include <tuple>
#include <vector>

/**
 * You are given a m x n matrix grid consisting of non-negative integers where grid[row][col]
 * represents the minimum time required to be able to visit the cell (row, col), which means you can
 * visit the cell (row, col) only when the time you visit it is greater than or equal to
 * grid[row][col].
 *
 * You are standing in the top-left cell of the matrix in the 0th second, and you must move to any
 * adjacent cell in the four directions: up, down, left, and right. Each move you make takes 1
 * second.
 *
 * Return the minimum time required in which you can visit the bottom-right cell of the matrix. If
 * you cannot visit the bottom-right cell, then return -1.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 1000
 * ! 4 <= m * n <= 10^5
 * ! 0 <= grid[i][j] <= 10^5
 * ! grid[0][0] == 0
 */

class Solution {
public:
    int minimumTime(std::vector<std::vector<int>>& grid)
    {
        if (grid[0][1] > 1 && grid[1][0] > 1)
            return -1;

        const int m = grid.size();
        const int n = grid[0].size();
        static constexpr std::array kDirections{std::make_pair(0, 1), std::make_pair(0, -1), std::make_pair(1, 0),
                                                std::make_pair(-1, 0)};
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[0][0] = true;
        using Tuple = std::tuple<int, int, int>; // <i, j, time>
        struct Compare {
            bool operator()(const Tuple& t1, const Tuple& t2) const
            {
                return std::get<2>(t1) > std::get<2>(t2);
            }
        };
        std::priority_queue<Tuple, std::vector<Tuple>, Compare> pq;
        pq.emplace(0, 0, 0);
        while (!pq.empty()) {
            const auto [i, j, time] = pq.top();
            pq.pop();
            if (i == m - 1 && j == n - 1)
                return time;

            for (const auto& [dx, dy] : kDirections) {
                const int x = i + dx;
                const int y = j + dy;
                if (x < 0 || x >= m || y < 0 || y >= n)
                    continue;

                if (visited[x][y])
                    continue;

                int arrivalTime = 0;
                if (grid[x][y] <= time + 1) {
                    arrivalTime = time + 1;
                } else if ((grid[x][y] - time) % 2) {
                    arrivalTime = grid[x][y];
                } else {
                    arrivalTime = grid[x][y] + 1;
                }
                visited[x][y] = true;
                pq.emplace(x, y, arrivalTime);
            }
        }
        return -1;
    }
};