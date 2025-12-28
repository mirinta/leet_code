#include <algorithm>
#include <vector>

/**
 * You are given a positive integer days representing the total number of days an employee is
 * available for work (starting from day 1). You are also given a 2D array meetings of size n where,
 * meetings[i] = [start_i, end_i] represents the starting and ending days of meeting i (inclusive).
 *
 * Return the count of days when the employee is available for work but no meetings are scheduled.
 *
 * Note: The meetings may overlap.
 *
 * ! 1 <= days <= 10^9
 * ! 1 <= meetings.length <= 10^5
 * ! meetings[i].length == 2
 * ! 1 <= meetings[i][0] <= meetings[i][1] <= days
 */

class Solution {
public:
    int countDays(int days, std::vector<std::vector<int>>& meetings)
    {
        std::sort(meetings.begin(), meetings.end(), [](const auto& v1, const auto& v2) { return v1[0] < v2[0]; });
        std::vector<std::vector<int>> merged;
        for (const auto& meeting : meetings) {
            if (merged.empty() || merged.back()[1] < meeting[0]) {
                merged.push_back(meeting);
            } else {
                merged.back()[1] = std::max(merged.back()[1], meeting[1]);
            }
        }
        int result = days;
        for (const auto& meeting : merged) {
            result -= meeting[1] - meeting[0] + 1;
        }
        return result;
    }
};