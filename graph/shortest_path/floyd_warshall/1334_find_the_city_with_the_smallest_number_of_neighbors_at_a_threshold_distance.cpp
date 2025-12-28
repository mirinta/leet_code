#include <vector>

/**
 * There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi,
 * weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the
 * integer distanceThreshold.
 *
 * Return the city with the smallest number of cities that are reachable through some path and whose
 * distance is at most distanceThreshold, If there are multiple such cities, return the city with
 * the greatest number.
 *
 * Notice that the distance of a path connecting cities i and j is equal to the sum of the edges'
 * weights along that path.
 *
 * ! 2 <= n <= 100
 * ! 1 <= edges.length <= n * (n - 1) / 2
 * ! edges[i].length == 3
 * ! 0 <= fromi < toi < n
 * ! 1 <= weighti, distanceThreshold <= 10^4
 * ! All pairs (fromi, toi) are distinct.
 */

class Solution {
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold)
    {
        const auto minDist = floyd(n, edges);
        int minCount = INT_MAX;
        int cityIndex = -1;
        for (int i = 0; i < n; ++i) {
            int count = 0;
            for (int j = 0; j < n; ++j) {
                if (i == j)
                    continue;

                if (minDist[i][j] <= distanceThreshold) {
                    count++;
                }
            }
            if (count < minCount) {
                minCount = count;
                cityIndex = i;
            } else if (count == minCount) {
                cityIndex = std::max(cityIndex, i);
            }
        }
        return cityIndex;
    }

private:
    std::vector<std::vector<int>> floyd(int n, const std::vector<std::vector<int>>& edges)
    {
        std::vector<std::vector<int>> minDist(n, std::vector<int>(n, INT_MAX));
        for (const auto& e : edges) {
            const auto& from = e[0];
            const auto& to = e[1];
            const auto& dist = e[2];
            minDist[from][to] = std::min(minDist[from][to], dist);
            minDist[to][from] = std::min(minDist[to][from], dist);
        }
        for (int i = 0; i < n; ++i) {
            minDist[i][i] = 0;
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                if (minDist[i][k] == INT_MAX)
                    continue;

                for (int j = 0; j < n; ++j) {
                    if (minDist[k][j] == INT_MAX)
                        continue;

                    minDist[i][j] = std::min(minDist[i][j], minDist[i][k] + minDist[k][j]);
                }
            }
        }
        return minDist;
    }
};