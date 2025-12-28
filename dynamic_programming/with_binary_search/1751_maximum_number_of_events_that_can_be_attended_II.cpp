#include <algorithm>
#include <vector>

/**
 * You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event
 * starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value
 * of valuei. You are also given an integer k which represents the maximum number of events you can
 * attend.
 *
 * You can only attend one event at a time. If you choose to attend an event, you must attend the
 * entire event. Note that the end day is inclusive: that is, you cannot attend two events where one
 * of them starts and the other ends on the same day.
 *
 * Return the maximum sum of values that you can receive by attending events.
 *
 * ! 1 <= k <= events.length
 * ! 1 <= k * events.length <= 10^6
 * ! 1 <= startDayi <= endDayi <= 10^9
 * ! 1 <= valuei <= 10^6
 */

class Solution {
public:
    int maxValue(std::vector<std::vector<int>>& events, int k)
    {
        // dp[i][j] = max score of attending at most j events of events[0:i-1]
        const int n = events.size();
        std::sort(events.begin(), events.end(), [](const auto& v1, const auto& v2) { return v1[1] < v2[1]; });
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(k + 1, INT_MIN));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 0;
        }
        auto compare = [](const auto& v, int val) { return v[1] < val; };
        int result = INT_MIN;
        for (int i = 1; i <= n; ++i) {
            const int start = events[i - 1][0];
            const int score = events[i - 1][2];
            for (int j = 1; j <= std::min(i, k); ++j) {
                auto iter = std::lower_bound(events.begin(), events.end(), start, compare);
                dp[i][j] = std::max(dp[i - 1][j], score + dp[iter - events.begin()][j - 1]);
                if (i == n) {
                    result = std::max(result, dp[i][j]);
                }
            }
        }
        return result;
    }
};