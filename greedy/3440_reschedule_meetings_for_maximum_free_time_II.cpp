#include <vector>

/**
 * You are given an integer eventTime denoting the duration of an event. You are also given two
 * integer arrays startTime and endTime, each of length n.
 *
 * These represent the start and end times of n non-overlapping meetings that occur during the event
 * between time t = 0 and time t = eventTime, where the ith meeting occurs during the time
 * [startTime[i], endTime[i]].
 *
 * You can reschedule at most one meeting by moving its start time while maintaining the same
 * duration, such that the meetings remain non-overlapping, to maximize the longest continuous
 * period of free time during the event.
 *
 * Return the maximum amount of free time possible after rearranging the meetings.
 *
 * Note that the meetings can not be rescheduled to a time outside the event and they should remain
 * non-overlapping.
 *
 * Note: In this version, it is valid for the relative ordering of the meetings to change after
 * rescheduling one meeting.
 *
 * ! 1 <= eventTime <= 10^9
 * ! n == startTime.length == endTime.length
 * ! 2 <= n <= 10^5
 * ! 0 <= startTime[i] < endTime[i] <= eventTime
 * ! endTime[i] <= startTime[i + 1] where i lies in the range [0, n - 2].
 */

class Solution {
public:
    int maxFreeTime(int eventTime, std::vector<int>& startTime, std::vector<int>& endTime)
    {
        const int n = startTime.size();
        // prefix[i] = max free time of event[0:i]
        std::vector<int> prefix(n);
        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                prefix[i] = startTime[i];
            } else {
                prefix[i] = std::max(prefix[i - 1], startTime[i] - endTime[i - 1]);
            }
        }
        // suffix[i] = max free time of event[i:n-1]
        std::vector<int> suffix(n);
        for (int i = n - 1; i >= 0; --i) {
            if (i == n - 1) {
                suffix[i] = eventTime - endTime[i];
            } else {
                suffix[i] = std::max(suffix[i + 1], startTime[i + 1] - endTime[i]);
            }
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int duration = endTime[i] - startTime[i];
            const int left = startTime[i] - (i == 0 ? 0 : endTime[i - 1]);
            const int right = (i == n - 1 ? eventTime : startTime[i + 1]) - endTime[i];
            result = std::max(result, right + left);
            if (duration <= (i == 0 ? 0 : prefix[i - 1]) || duration <= (i == n - 1 ? 0 : suffix[i + 1])) {
                result = std::max(result, duration + left + right);
            }
        }
        return result;
    }
};
