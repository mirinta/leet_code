#include <queue>
#include <vector>

/**
 * You are given a 0-indexed 2D integer array grid of size m x n that represents a map of the items
 * in a shop. The integers in the grid represent the following:
 *
 * - 0 represents a wall that you cannot pass through.
 *
 * - 1 represents an empty cell that you can freely move to and from.
 *
 * - All other positive integers represent the price of an item in that cell. You may also freely
 * move to and from these item cells. It takes 1 step to travel between adjacent grid cells.
 *
 * You are also given integer arrays pricing and start where pricing = [low, high] and start = [row,
 * col] indicates that you start at the position (row, col) and are interested only in items with a
 * price in the range of [low, high] (inclusive). You are further given an integer k.
 *
 * You are interested in the positions of the k highest-ranked items whose prices are within the
 * given price range. The rank is determined by the first of these criteria that is different:
 *
 * 1. Distance, defined as the length of the shortest path from the start (shorter distance has a
 * higher rank).
 *
 * 2. Price (lower price has a higher rank, but it must be in the price range).
 *
 * 3. The row number (smaller row number has a higher rank).
 *
 * 4. The column number (smaller column number has a higher rank).
 *
 * Return the k highest-ranked items within the price range sorted by their rank (highest to
 * lowest). If there are fewer than k reachable items within the price range, return all of them.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 1 <= m, n <= 10^5
 * ! 1 <= m * n <= 10^5
 * ! 0 <= grid[i][j] <= 10^5
 * ! pricing.length == 2
 * ! 2 <= low <= high <= 10^5
 * ! start.length == 2
 * ! 0 <= row <= m - 1
 * ! 0 <= col <= n - 1
 * ! grid[row][col] > 0
 * ! 1 <= k <= m * n
 */

class Solution {
public:
    std::vector<std::vector<int>> highestRankedKItems(std::vector<std::vector<int>>& grid,
                                                      std::vector<int>& pricing,
                                                      std::vector<int>& start,
                                                      int k)
    {
        static const std::vector<std::pair<int, int>> kDirections{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        const int m = grid.size();
        const int n = grid[0].size();
        std::vector<std::vector<int>> distTo(m, std::vector<int>(n, INT_MAX));
        distTo[start[0]][start[1]] = 0;
        std::queue<std::pair<int, int>> queue;
        queue.emplace(start[0], start[1]);
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[start[0]][start[1]] = true;
        std::priority_queue<Tuple, std::vector<Tuple>, Compare> pq;
        while (!queue.empty()) {
            for (int t = queue.size(); t > 0; --t) {
                const auto [x, y] = queue.front();
                queue.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (grid[i][j] == 0 || visited[i][j])
                        continue;

                    visited[i][j] = true;
                    distTo[i][j] = 1 + distTo[x][y];
                    queue.emplace(i, j);
                }
                if (grid[x][y] > 1 && grid[x][y] >= pricing[0] && grid[x][y] <= pricing[1]) {
                    pq.emplace(distTo[x][y], grid[x][y], x, y);
                    if (pq.size() > k) {
                        pq.pop();
                    }
                }
            }
        }
        std::vector<std::vector<int>> result(pq.size());
        for (int i = result.size() - 1; i >= 0; --i) {
            const auto [dist, price, row, col] = pq.top();
            pq.pop();
            result[i] = {row, col};
        }
        return result;
    }

private:
    using Tuple = std::tuple<int, int, int, int>; // <dist, price, row, col>

    struct Compare {
        bool operator()(const Tuple& a, const Tuple& b)
        {
            const auto& [dist1, price1, row1, col1] = a;
            const auto& [dist2, price2, row2, col2] = b;
            if (dist1 != dist2)
                return dist1 < dist2;

            if (price1 != price2)
                return price1 < price2;

            if (row1 != row2)
                return row1 < row2;

            return col1 < col2;
        }
    };
};