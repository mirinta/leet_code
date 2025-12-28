#include <vector>

/**
 * You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work on the ith job,
 * you have to finish all the jobs j where 0 <= j < i).
 *
 * You have to finish at least one task every day. The difficulty of a job schedule is the sum of
 * difficulties of each day of the d days. The difficulty of a day is the maximum difficulty of a
 * job done on that day.
 *
 * You are given an integer array jobDifficulty and an integer d. The difficulty of the ith job is
 * jobDifficulty[i].
 *
 * Return the minimum difficulty of a job schedule. If you cannot find a schedule for the jobs
 * return -1.
 *
 * ! 1 <= jobDifficulty.length <= 300
 * ! 0 <= jobDifficulty[i] <= 1000
 * ! 1 <= d <= 10
 */

class Solution {
public:
    int minDifficulty(std::vector<int>& jobDifficulty, int d)
    {
        if (jobDifficulty.size() < d)
            return -1;

        // dp[i][t] = min difficulty of scheduling jobs[0:i-1] within t days
        const int n = jobDifficulty.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(d + 1, INT_MAX / 2));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int t = 1; t <= std::min(i, d); ++t) {
                for (int k = i, max = INT_MIN; k >= t; --k) {
                    max = std::max(max, jobDifficulty[k - 1]);
                    dp[i][t] = std::min(dp[i][t], dp[k - 1][t - 1] + max);
                }
            }
        }
        return dp[n][d] == INT_MAX / 2 ? -1 : dp[n][d];
    }
};