#include <queue>
#include <vector>

/**
 * Given an m x n integer matrix heightMap representing the height of each unit cell in a 2D
 * elevation map, return the volume of water it can trap after raining.
 *
 * ! m == heightMap.length
 * ! n == heightMap[i].length
 * ! 1 <= m, n <= 200
 * ! 0 <= heightMap[i][j] <= 2 * 10^4
 */

class Solution {
public:
    int trapRainWater(std::vector<std::vector<int>>& heightMap)
    {
        const int m = heightMap.size();
        const int n = heightMap[0].size();
        using Tuple = std::tuple<int, int, int>; // x, y, height
        auto comparator = [](const auto& t1, const auto& t2) { return std::get<2>(t1) > std::get<2>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(comparator);
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            visited[i][0] = true;
            pq.emplace(i, 0, heightMap[i][0]);
            visited[i][n - 1] = true;
            pq.emplace(i, n - 1, heightMap[i][n - 1]);
        }
        for (int j = 1; j < n - 1; ++j) {
            visited[0][j] = true;
            pq.emplace(0, j, heightMap[0][j]);
            visited[m - 1][j] = true;
            pq.emplace(m - 1, j, heightMap[m - 1][j]);
        }
        int seaLevel = 0;
        int result = 0;
        while (!pq.empty()) {
            const auto [x, y, h] = pq.top();
            pq.pop();
            seaLevel = std::max(seaLevel, h);
            result += seaLevel - h;
            for (const auto& [dx, dy] : kDirections) {
                const int i = x + dx;
                const int j = y + dy;
                if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j])
                    continue;

                visited[i][j] = true;
                pq.emplace(i, j, heightMap[i][j]);
            }
        }
        return result;
    }

private:
    const std::vector<std::pair<int, int>> kDirections{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
};
