#include <climits>
#include <vector>

/**
 * Given a 0-indexed integer array nums of size n, find the maximum difference between nums[i] and
 * nums[j] (i.e., nums[j] - nums[i]), such that 0 <= i < j < n and nums[i] < nums[j].
 *
 * Return the maximum difference. If no such i and j exists, return -1.
 *
 * ! n == nums.length
 * ! 2 <= n <= 1000
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int maximumDifference(std::vector<int>& nums)
    {
        int min = INT_MAX;
        int result = 0;
        for (const auto& val : nums) {
            if (min != INT_MAX && min != val) {
                result = std::max(result, val - min);
            }
            min = std::min(min, val);
        }
        return result == 0 ? -1 : result;
    }
};
