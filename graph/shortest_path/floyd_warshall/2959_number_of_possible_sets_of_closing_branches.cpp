#include <vector>

/**
 * There is a company with n branches across the country, some of which are connected by roads.
 * Initially, all branches are reachable from each other by traveling some roads.
 *
 * The company has realized that they are spending an excessive amount of time traveling between
 * their branches. As a result, they have decided to close down some of these branches (possibly
 * none). However, they want to ensure that the remaining branches have a distance of at most
 * maxDistance from each other.
 *
 * The distance between two branches is the minimum total traveled length needed to reach one branch
 * from another.
 *
 * You are given integers n, maxDistance, and a 0-indexed 2D array roads, where roads[i] = [ui, vi,
 * wi] represents the undirected road between branches ui and vi with length wi.
 *
 * Return the number of possible sets of closing branches, so that any branch has a distance of at
 * most maxDistance from any other.
 *
 *
 * Note that, after closing a branch, the company will no longer have access to any roads connected
 * to it.
 *
 * Note that, multiple roads are allowed.
 *
 * ! 1 <= n <= 10
 * ! 1 <= maxDistance <= 105
 * ! 0 <= roads.length <= 1000
 * ! roads[i].length == 3
 * ! 0 <= ui, vi <= n - 1
 * ! ui != vi
 * ! 1 <= wi <= 1000
 * ! All branches are reachable from each other by traveling some roads.
 */

class Solution {
public:
    int numberOfSets(int n, int maxDistance, std::vector<std::vector<int>>& roads)
    {
        // since 1 <= n <= 10,
        // we can enumerate all possible sets using binary mask
        int result = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (isValid(mask, n, maxDistance, roads)) {
                result++;
            }
        }
        return result;
    }

private:
    bool isClosed(int i, int mask)
    {
        return mask & (1 << i);
    }

    bool isValid(int mask, int n, int maxDistance, const std::vector<std::vector<int>>& roads)
    {
        // Floyd shortest path
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, INT_MAX / 2));
        for (const auto& road : roads) {
            if (isClosed(road[0], mask) || isClosed(road[1], mask))
                continue;

            // NOTE: it may contain duplicate roads, we only take the minimum one
            dist[road[0]][road[1]] = std::min(dist[road[0]][road[1]], road[2]);
            dist[road[1]][road[0]] = dist[road[0]][road[1]];
        }
        for (int i = 0; i < n; ++i) {
            dist[i][i] = 0;
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (isClosed(i, mask))
                continue;

            for (int j = 0; j < n; ++j) {
                if (i == j || isClosed(j, mask))
                    continue;

                if (dist[i][j] > maxDistance)
                    return false;
            }
        }
        return true;
    }
};