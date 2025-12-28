#include <algorithm>
#include <vector>

/**
 * Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration
 * duration, return the earliest time slot that works for both of them and is of duration duration.
 *
 * If there is no common time slot that satisfies the requirements, return an empty array.
 *
 * The format of a time slot is an array of two elements [start, end] representing an inclusive time
 * range from start to end.
 *
 * It is guaranteed that no two availability slots of the same person intersect with each other.
 * That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either
 * start1 > end2 or start2 > end1.
 *
 * ! 1 <= slots1.length, slots2.length <= 10^4
 * ! slots1[i].length, slots2[i].length == 2
 * ! slots1[i][0] < slots1[i][1]
 * ! slots2[i][0] < slots2[i][1]
 * ! 0 <= slots1[i][j], slots2[i][j] <= 10^9
 * ! 1 <= duration <= 10^6
 */

class Solution {
public:
    std::vector<int>
        minAvailableDuration(std::vector<std::vector<int>>& slots1, std::vector<std::vector<int>>& slots2, int duration)
    {
        std::sort(slots1.begin(), slots1.end(), [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        std::sort(slots2.begin(), slots2.end(), [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        int i = 0;
        int j = 0;
        while (i < slots1.size() && j < slots2.size()) {
            const int start = std::max(slots1[i][0], slots2[j][0]);
            const int end = std::min(slots1[i][1], slots2[j][1]);
            if (end - start >= duration)
                return {start, start + duration};

            if (slots1[i][1] < slots2[j][1]) {
                i++;
            } else {
                j++;
            }
        }
        return {};
    }
};