#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at
 * startDayi and ends at endDayi.
 *
 * You can attend an event i at any day d where startTimei <= d <= endTimei. You can only attend one
 * event at any time d.
 *
 * Return the maximum number of events you can attend.
 *
 * ! 1 <= events.length <= 10^5
 * ! events[i].length == 2
 * ! 1 <= startDayi <= endDayi <= 10^5
 */

class Solution {
public:
    int maxEvents(std::vector<std::vector<int>>& events)
    {
        const int n = events.size();
        std::sort(events.begin(), events.end(), [](const auto& e1, const auto& e2) { return e1[0] < e2[0]; });
        int maxDay = 0;
        for (const auto& e : events) {
            maxDay = std::max(maxDay, e[1]);
        }
        std::priority_queue<int, std::vector<int>, std::greater<>> pq;
        int result = 0;
        for (int day = events[0][0], i = 0; day <= maxDay; ++day) {
            while (i < n && events[i][0] <= day) {
                pq.emplace(events[i][1]);
                i++;
            }
            while (!pq.empty() && pq.top() < day) {
                pq.pop();
            }
            if (!pq.empty()) {
                pq.pop();
                result++;
            }
        }
        return result;
    }
};
