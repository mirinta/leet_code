#include <algorithm>
#include <queue>
#include <vector>

/**
 * There are n different online courses numbered from 1 to n. You are given an array courses where
 * courses[i] = [durationi, lastDayi] indicate that the ith course should be taken continuously for
 * durationi days and must be finished before or on lastDayi.
 *
 * You will start on the 1st day and you cannot take two or more courses simultaneously.
 *
 * Return the maximum number of courses that you can take.
 *
 * ! 1 <= courses.length <= 10^4
 * ! 1 <= durationi, lastDayi <= 10^4
 */

class Solution {
public:
    int scheduleCourse(std::vector<std::vector<int>>& courses)
    {
        std::sort(courses.begin(), courses.end(), [](const auto& c1, const auto& c2) { return c1[1] < c2[1]; });
        std::priority_queue<int> pq; // max heap, durations
        int days = 0;
        for (const auto& course : courses) {
            days += course[0];
            pq.emplace(course[0]);
            if (days > course[1]) {
                days -= pq.top();
                pq.pop();
            }
        }
        return pq.size();
    }
};