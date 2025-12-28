#include <algorithm>
#include <vector>

/**
 * On a campus represented as a 2D grid, there are n workers and m bikes, with n <= m. Each worker
 * and bike is a 2D coordinate on this grid.
 *
 * We assign one unique bike to each worker so that the sum of the Manhattan distances between each
 * worker and their assigned bike is minimized.
 *
 * Return the minimum possible sum of Manhattan distances between each worker and their assigned
 * bike.
 *
 * The Manhattan distance between two points p1 and p2 is Manhattan(p1, p2) = |p1.x - p2.x| + |p1.y
 * - p2.y|.
 *
 *
 * ! n == workers.length
 * ! m == bikes.length
 * ! 1 <= n <= m <= 10
 * ! workers[i].length == 2
 * ! bikes[i].length == 2
 * ! 0 <= workers[i][0], workers[i][1], bikes[i][0], bikes[i][1] < 1000
 * ! All the workers and the bikes locations are unique.
 */

#include <climits>
#include <vector>

class Solution {
public:
    int assignBikes(std::vector<std::vector<int>>& workers, std::vector<std::vector<int>>& bikes)
    {
        const int n = workers.size();
        const int m = bikes.size();
        // dp[i][state] = min sum of distances of assigning i bikes to workers[0:i)
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(1 << m, INT_MAX / 2));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int state = 0; state < (1 << m); ++state) {
                if (countSetBits(state) != i)
                    continue;

                for (int j = 0; j < m; ++j) {
                    if ((state >> j) & 1) {
                        dp[i][state] =
                            std::min(dp[i][state], dp[i - 1][state ^ (1 << j)] + dist(workers[i - 1], bikes[j]));
                    }
                }
            }
        }
        return *std::min_element(dp[n].begin(), dp[n].end());
    }

private:
    int dist(const std::vector<int>& worker, const std::vector<int>& bike)
    {
        return std::abs(worker[0] - bike[0]) + std::abs(worker[1] - bike[1]);
    }

    int countSetBits(int val)
    {
        int result = 0;
        while (val) {
            result++;
            val &= val - 1;
        }
        return result;
    }
};
