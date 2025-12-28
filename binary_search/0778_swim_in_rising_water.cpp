#include <queue>
#include <vector>

/**
 * You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation
 * at that point (i, j).
 *
 * The rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a
 * square to another 4-directionally adjacent square if and only if the elevation of both squares
 * individually are at most t. You can swim infinite distances in zero time. Of course, you must
 * stay within the boundaries of the grid during your swim.
 *
 * Return the least time until you can reach the bottom right square (n - 1, n - 1) if you start at
 * the top left square (0, 0).
 *
 * ! n == grid.length
 * ! n == grid[i].length
 * ! 1 <= n <= 50
 * ! 0 <= grid[i][j] < n2
 * ! Each value grid[i][j] is unique.
 */

class Solution {
public:
    int swimInWater(std::vector<std::vector<int>>& grid)
    {
        return approach2(grid);
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    // PQ, TC = O(N^2log(N^2)), SC = O(N^2)
    int approach2(const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        visited[0][0] = true;
        using Tuple = std::tuple<int, int, int>; // <height, x, y>
        auto comparator = [](const auto& t1, const auto& t2) { return std::get<0>(t1) > std::get<0>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(comparator);
        pq.emplace(grid[0][0], 0, 0);
        int time = 0;
        while (!pq.empty()) {
            const auto [height, x, y] = pq.top();
            pq.pop();
            time = std::max(time, height);
            if (x == n - 1 && y == n - 1)
                return time;

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= n || j < 0 || j >= n)
                    continue;

                if (!visited[i][j]) {
                    visited[i][j] = true;
                    pq.emplace(grid[i][j], i, j);
                }
            }
        }
        return -1;
    }

    // binary search + BFS, TC = O(N^2log(N^2)), SC = O(N^2)
    int approach1(const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        int lo = grid[0][0];
        int hi = n * n;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, grid)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

    bool isValid(int max, const std::vector<std::vector<int>>& grid)
    {
        const int n = grid.size();
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
        visited[0][0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(0, 0);
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (x == n - 1 && y == n - 1)
                    return true;

                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= n || j < 0 || j >= n)
                        continue;

                    if (!visited[i][j] && grid[i][j] <= max) {
                        visited[i][j] = true;
                        queue.emplace(i, j);
                    }
                }
            }
        }
        return false;
    }
};
const std::vector<std::pair<int, int>> Solution::kDirections{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};