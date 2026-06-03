#include <vector>

/**
 * You are given two categories of them park attractions: land rides and water rides.
 *
 * Land rides
 *
 * - landStartTime[i] - the earliest time the ith land ride can be boarded.
 *
 * - landDuration[i] - how long the ith land ride lasts.
 *
 * Water rides
 *
 * - waterStartTime[j] - the earliest time the jth water ride can be boarded.
 *
 * - waterDuration[j] - how long the jth water ride lasts.
 *
 * A tourist must experience exactly one ride from each category, in either order.
 *
 * - A ride may be stared at its opening time or any later moment.
 *
 * - If a ride is started at time t, it finishes at time t + duration.
 *
 * - Immediately after finishing one ride the tourist may board the other (if it is already open) or wait until it
 * opens.
 *
 * Return the earliest possible time at which the tourist can finish both rides.
 *
 * ! 1 <= n, m <= 100
 * ! landStartTime.length = landDuration.length == n
 * ! waterStartTime.length = waterDuration.length == m
 * ! 1 <= landStartTime[i], landDuration[i], waterStartTime[j], waterDuration[j] <= 1000
 */

class Solution {
public:
    int earliestFinishTime(std::vector<int>& landStartTime,
                           std::vector<int>& landDuration,
                           std::vector<int>& waterStartTime,
                           std::vector<int>& waterDuration)
    {
        const int case1 = solve(landStartTime, landDuration, waterStartTime, waterDuration);
        const int case2 = solve(waterStartTime, waterDuration, landStartTime, landDuration);
        return std::min(case1, case2);
    }

private:
    using Vec = std::vector<int>;

    int solve(const Vec& start1, const Vec& duration1, const Vec& start2, const Vec& duration2)
    {
        const int m = start1.size();
        const int n = start2.size();
        int finish1 = INT_MAX;
        for (int i = 0; i < m; ++i) {
            finish1 = std::min(finish1, start1[i] + duration1[i]);
        }
        int finish2 = INT_MAX;
        for (int j = 0; j < n; ++j) {
            finish2 = std::min(finish2, std::max(finish1, start2[j]) + duration2[j]);
        }
        return finish2;
    }
};