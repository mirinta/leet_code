#include <vector>

/**
 * A set of real numbers can be represented as the union of several disjoint intervals, where each
 * interval is in the form [a, b). A real number x is in the set if one of its intervals [a, b)
 * contains x (i.e. a <= x < b).
 *
 * You are given a sorted list of disjoint intervals intervals representing a set of real numbers as
 * described above, where intervals[i] = [ai, bi] represents the interval [ai, bi). You are also
 * given another interval toBeRemoved.
 *
 * Return the set of real numbers with the interval toBeRemoved removed from intervals. In other
 * words, return the set of real numbers such that every x in the set is in intervals but not in
 * toBeRemoved. Your answer should be a sorted list of disjoint intervals as described above.
 *
 * ! 1 <= intervals.length <= 10^4
 * ! -10^9 <= ai < bi <= 10^9
 */

class Solution {
public:
    std::vector<std::vector<int>> removeInterval(std::vector<std::vector<int>>& intervals,
                                                 std::vector<int>& toBeRemoved)
    {
        std::vector<std::vector<int>> result;
        const auto start = toBeRemoved[0];
        const auto end = toBeRemoved[1];
        for (const auto& interval : intervals) {
            const auto a = interval[0];
            const auto b = interval[1];
            if ((b <= start) || (a >= end)) {
                //       start----end
                // a1----b1        a2----b2
                result.push_back(interval);
                continue;
            }
            if (a < start) {
                //    start----end
                // a--------b
                result.push_back({a, start});
            }
            if (b > end) {
                //    start----end
                //           a-------b
                result.push_back({end, b});
            }
        }
        return result;
    }
};