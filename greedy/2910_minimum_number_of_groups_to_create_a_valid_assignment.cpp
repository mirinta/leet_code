#include <cmath>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums of length n.
 *
 * We want to group the indices so for each index i in the range [0, n - 1], it is assigned to
 * exactly one group.
 *
 * A group assignment is valid if the following conditions hold:
 *
 * - For every group g, all indices i assigned to group g have the same value in nums.
 *
 * - For any two groups g1 and g2, the difference between the number of indices assigned to g1 and
 * g2 should not exceed 1.
 *
 * Return an integer denoting the minimum number of groups needed to create a valid group
 * assignment.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int minGroupsForValidAssignment(std::vector<int>& nums)
    {
        std::unordered_map<int, int> map; // value to frequency
        for (const auto& val : nums) {
            map[val]++;
        }
        int minFreq = nums.size();
        for (const auto& [_, freq] : map) {
            minFreq = std::min(minFreq, freq);
        }
        // if freqA = 10 and freqB = 32, let sz = 10:
        // - #groupsOfA = 1, remainder = 0 => 1 group, group.size = 10
        // - #groupsOfB = 3, remainder = 2 => 3 groups, two of size 11, one of size 10, OK
        // if freqA = 10 and freqB = 33, let sz = 10:
        // - #groupsOfA = 1, remainder = 0 => 1 group, group.size = 10
        // - #groupsOfB = 3, remainder = 3 => 3 groups, all of size 11, OK
        // if freqA = 10 and freqB = 34, let sz = 10:
        // - #groupsOfA = 1, remainder = 0 => 1 group, group.size = 10
        // - #groupsOfB = 3, remainder = 4 => 4 groups, three of size 11, one of size 1, WRONG!
        for (int sz = minFreq; sz >= 1; --sz) {
            int result = 0;
            for (const auto& [_, freq] : map) {
                const int remainder = freq % sz;
                const int groups = freq / sz;
                if (remainder > groups) {
                    result = 0;
                    break;
                }
                result += std::ceil(freq * 1.0 / (sz + 1));
            }
            if (result > 0)
                return result;
        }
        return -1;
    }
};
