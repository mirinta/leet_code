#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given an integer n. There are n rooms numbered from 0 to n - 1.
 *
 * You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting
 * will be held during the half-closed time interval [starti, endi). All the values of starti are
 * unique.
 *
 * Meetings are allocated to rooms in the following manner:
 *
 * Each meeting will take place in the unused room with the lowest number.
 * If there are no available rooms, the meeting will be delayed until a room becomes free. The
 * delayed meeting should have the same duration as the original meeting. When a room becomes
 * unused, meetings that have an earlier original start time should be given the room. Return the
 * number of the room that held the most meetings. If there are multiple rooms, return the room with
 * the lowest number.
 *
 * A half-closed interval [a, b) is the interval between a and b including a and not including b.
 *
 * ! 1 <= n <= 100
 * ! 1 <= meetings.length <= 10^5
 * ! meetings[i].length == 2
 * ! 0 <= starti < endi <= 5 * 10^5
 * ! All the values of starti are unique.
 */

class Solution
{
public:
    int mostBooked(int n, std::vector<std::vector<int>>& meetings)
    {
        std::sort(meetings.begin(), meetings.end());
        std::vector<int> count(n, 0);
        std::priority_queue<int, std::vector<int>, std::greater<>> unused; // room id
        for (int i = 0; i < n; ++i) {
            unused.emplace(i);
        }
        using Pair = std::pair<long long, int>; // <actual end time, root id>
        auto compare = [](const auto& p1, const auto& p2) {
            if (p1.first == p2.first)
                return p1.second > p2.second;

            return p1.first > p2.first;
        };
        std::priority_queue<Pair, std::vector<Pair>, decltype(compare)> used(compare);
        for (const auto& meeting : meetings) {
            while (!used.empty() && used.top().first <= meeting[0]) {
                unused.emplace(used.top().second);
                used.pop();
            }
            if (unused.empty()) {
                const auto [endTime, room] = used.top();
                used.pop();
                count[room]++;
                used.emplace(endTime + meeting[1] - meeting[0], room);
            } else {
                const auto room = unused.top();
                unused.pop();
                count[room]++;
                used.emplace(meeting[1], room);
            }
        }
        return std::max_element(count.begin(), count.end()) - count.begin();
    }
};
