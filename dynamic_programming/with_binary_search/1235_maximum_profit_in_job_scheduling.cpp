#include <algorithm>
#include <array>
#include <vector>

/**
 * We have n jobs, where every job is scheduled to be done from startTime[i] to endTime[i],
 * obtaining a profit of profit[i].
 *
 * You're given the startTime, endTime and profit arrays, return the maximum profit you can take
 * such that there are no two jobs in the subset with overlapping time range.
 *
 * If you choose a job that ends at time X you will be able to start another job that starts at time
 * X.
 *
 * ! 1 <= startTime.length == endTime.length == profit.length <= 5 * 10^4
 * ! 1 <= startTime[i] < endTime[i] <= 10^9
 * ! 1 <= profit[i] <= 10^4
 */

class Solution {
public:
    int jobScheduling(std::vector<int>& startTime, std::vector<int>& endTime, std::vector<int>& profit)
    {
        // dp[i] = max profit of the valid subsequence of jobs[0:i-1] ending at jobs[i-1]
        const int n = profit.size();
        std::vector<std::array<int, 3>> jobs(n);
        for (int i = 0; i < n; ++i) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        std::sort(jobs.begin(), jobs.end(), [](const auto& t1, const auto& t2) { return t1[1] < t2[1]; });
        std::vector<int> dp(n + 1, 0);
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            const int start = jobs[i - 1][0];
            const int score = jobs[i - 1][2];
            auto iter =
                std::upper_bound(jobs.begin(), jobs.end(), start, [](int val, const auto& v) { return v[1] > val; });
            dp[i] = std::max(dp[i - 1], dp[iter - jobs.begin()] + score);
            result = std::max(result, dp[i]);
        }
        return result;
    }
};