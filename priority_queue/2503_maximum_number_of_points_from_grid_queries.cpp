#include <algorithm>
#include <queue>
#include <tuple>
#include <vector>

/**
 * You are given an m x n integer matrix grid and an array queries of size k.
 *
 * Find an array answer of size k such that for each integer queries[i] you start in the top left
 * cell of the matrix and repeat the following process:
 *
 * - If queries[i] is strictly greater than the value of the current cell that you are in, then you
 * get one point if it is your first time visiting this cell, and you can move to any adjacent cell
 * in all 4 directions: up, down, left, and right.
 *
 * - Otherwise, you do not get any points, and you end this process.
 *
 * After the process, answer[i] is the maximum number of points you can get. Note that for each
 * query you are allowed to visit the same cell multiple times.
 *
 * Return the resulting array answer.
 *
 * ! m == grid.length
 * ! n == grid[i].length
 * ! 2 <= m, n <= 1000
 * ! 4 <= m * n <= 10^5
 * ! k == queries.length
 * ! 1 <= k <= 10^4
 * ! 1 <= grid[i][j], queries[i] <= 10^6
 */

class Solution {
public:
    std::vector<int> maxPoints(std::vector<std::vector<int>>& grid, std::vector<int>& queries)
    {
        const int m = grid.size();
        const int n = grid[0].size();
        static const std::vector<std::pair<int, int>> kDirections{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        std::vector<std::pair<int, int>> q(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            q[i].first = queries[i];
            q[i].second = i;
        }
        std::sort(q.begin(), q.end(), [](const auto& q1, const auto& q2) { return q1.first < q2.first; });
        using Tuple = std::tuple<int, int, int>;
        auto compare = [&](const auto& t1, const auto& t2) { return std::get<0>(t1) > std::get<0>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(compare)> pq(compare);
        pq.emplace(grid[0][0], 0, 0);
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[0][0] = true;
        int count = 0;
        std::vector<int> result(queries.size());
        for (const auto& [limit, idx] : q) {
            while (!pq.empty() && std::get<0>(pq.top()) < limit) {
                count++;
                const auto [val, x, y] = pq.top();
                pq.pop();
                for (const auto& [dx, dy] : kDirections) {
                    const int i = x + dx;
                    const int j = y + dy;
                    if (i < 0 || i >= m || j < 0 || j >= n)
                        continue;

                    if (!visited[i][j]) {
                        visited[i][j] = true;
                        pq.emplace(grid[i][j], i, j);
                    }
                }
            }
            result[idx] = count;
        }
        return result;
    }
};
