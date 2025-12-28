#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei,
 * valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event,
 * you will receive a value of valuei. You can choose at most two non-overlapping events to attend
 * such that the sum of their values is maximized.
 *
 * Return this maximum sum.
 *
 * Note that the start time and end time is inclusive: that is, you cannot attend two events where
 * one of them starts and the other ends at the same time. More specifically, if you attend an event
 * with end time t, the next event must start at or after t + 1.
 *
 * ! 2 <= events.length <= 10^5
 * ! events[i].length == 3
 * ! 1 <= startTimei <= endTimei <= 10^9
 * ! 1 <= valuei <= 10^6
 */

class Solution {
public:
    int maxTwoEvents(std::vector<std::vector<int>>& events)
    {
        const int n = events.size();
        std::sort(events.begin(), events.end(), [](const auto& e1, const auto& e2) { return e1[1] < e2[1]; });
        std::vector<int> prefixMax(n);
        prefixMax[0] = events[0][2];
        for (int i = 1; i < n; ++i) {
            prefixMax[i] = std::max(prefixMax[i - 1], events[i][2]);
        }
        int result = 0;
        for (const auto& e : events) {
            auto iter = std::lower_bound(events.begin(), events.end(), e[0],
                                         [](const auto& event, int val) { return event[1] < val; });
            if (iter == events.begin()) {
                result = std::max(result, e[2]);
            } else {
                result = std::max(result, e[2] + prefixMax[std::distance(events.begin(), std::prev(iter))]);
            }
        }
        return result;
    }
};