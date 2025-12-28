#include <queue>
#include <tuple>
#include <vector>

/**
 * Your are a hiker preparing for an upcoming hike. You are given "heights", a 2D array of size row
 * x columns, where hights[row][col] represents the height of cell (row, col). You are situated in
 * the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows - 1, columns -
 * 1). You can move up, down, left, or right, and you wish to find a route that requires the minimum
 * effort.
 *
 * A route's effort is the maximum absolute difference in heights between two consecutive cells of
 * the route.
 *
 * Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
 *
 * ! rows == heights.length
 * ! columns == heights[i].length
 * ! 1 <= rows, columns <= 100
 * ! 1 <= heights[i][j] <= 10^6
 */

class Solution {
public:
    int minimumEffortPath(std::vector<std::vector<int>>& heights)
    {
        return approach1(heights);
    }

private:
    static const std::vector<std::pair<int, int>> kDirections;

    // binary search + BFS, TC = O(MNlog(1e6)), SC = O(MN)
    int approach2(const std::vector<std::vector<int>>& heights)
    {
        int lo = 0;
        int hi = 1e6;
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, heights)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

    bool isValid(int max, const std::vector<std::vector<int>>& heights)
    {
        const int m = heights.size();
        const int n = heights[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[0][0] = true;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(0, 0);
        while (!queue.empty()) {
            for (int k = queue.size(); k > 0; --k) {
                const auto [x, y] = queue.front();
                queue.pop();
                if (x == m - 1 && y == n - 1)
                    return true;

                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j])
                        continue;

                    if (std::abs(heights[x][y] - heights[i][j]) <= max) {
                        visited[i][j] = true;
                        queue.emplace(i, j);
                    }
                }
            }
        }
        return false;
    }

    // dijkstra, TC = O(MNlogMN), SC = O(MN)
    int approach1(const std::vector<std::vector<int>>& heights)
    {
        const int m = heights.size();
        const int n = heights[0].size();
        std::vector<std::vector<int>> effortTo(m, std::vector<int>(n, INT_MAX));
        effortTo[0][0] = 0;
        using Tuple = std::tuple<int, int, int>; // <effort, x, y>
        auto compare = [](const auto& t1, const auto& t2) { return std::get<0>(t1) > std::get<0>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(compare)> pq(compare);
        pq.emplace(0, 0, 0);
        while (!pq.empty()) {
            const auto [effort, x, y] = pq.top();
            pq.pop();
            if (x == m - 1 && y == n - 1)
                return effort;

            if (effort > effortTo[x][y])
                continue;

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n)
                    continue;

                const int diff = std::abs(heights[x][y] - heights[i][j]);
                if (effortTo[i][j] > std::max(effort, diff)) {
                    effortTo[i][j] = std::max(effort, diff);
                    pq.emplace(effortTo[i][j], i, j);
                }
            }
        }
        return -1;
    }
};
const std::vector<std::pair<int, int>> Solution::kDirections{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};