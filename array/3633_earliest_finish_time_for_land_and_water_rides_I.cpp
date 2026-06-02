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
        const int m = landStartTime.size();
        const int n = waterStartTime.size();
        int result = INT_MAX;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                const int landRide = landStartTime[i] + landDuration[i];
                result = std::min(result, landRide + std::max(0, waterStartTime[j] - landRide) + waterDuration[j]);
                const int waterRide = waterStartTime[j] + waterDuration[j];
                result = std::min(result, waterRide + std::max(0, landStartTime[i] - waterRide) + landDuration[i]);
            }
        }
        return result;
    }
};