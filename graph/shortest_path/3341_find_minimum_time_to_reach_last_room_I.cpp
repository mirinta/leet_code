#include <climits>
#include <queue>
#include <tuple>
#include <vector>

/**
 * There is a dungeon with n x m rooms arranged as a grid.
 *
 * You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time
 * in seconds when you can start moving to that room. You start from the room (0, 0) at time t = 0
 * and can move to an adjacent room. Moving between adjacent rooms takes exactly one second.
 *
 * Return the minimum time to reach the room (n - 1, m - 1).
 *
 * Two rooms are adjacent if they share a common wall, either horizontally or vertically.
 *
 * ! 2 <= n == moveTime.length <= 50
 * ! 2 <= m == moveTime[i].length <= 50
 * ! 0 <= moveTime[i][j] <= 10^9
 */

class Solution
{
public:
    int minTimeToReach(std::vector<std::vector<int>>& moveTime)
    {
        const int m = moveTime.size();
        const int n = moveTime[0].size();
        static const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        using Tuple = std::tuple<int, int, int>; // <t, x, y>
        auto compare = [](const Tuple& t1, const Tuple& t2) {
            return std::get<0>(t1) > std::get<0>(t2);
        };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(compare)> pq(compare);
        pq.emplace(0, 0, 0);
        std::vector<std::vector<int>> timeTo(m, std::vector<int>(n, INT_MAX));
        timeTo[0][0] = 0;
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[0][0] = true;
        while (!pq.empty()) {
            const auto [t, x, y] = pq.top();
            pq.pop();
            if (t > timeTo[x][y])
                continue;

            if (x == m - 1 && y == n - 1)
                return t;

            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j])
                    continue;

                const int eta = std::max(t, moveTime[i][j]) + 1;
                if (timeTo[i][j] > eta) {
                    visited[i][j] = true;
                    moveTo[i][j] = eta;
                    pq.emplace(eta, i, j);
                }
            }
        }
        return -1;
    }
};
