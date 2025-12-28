#include <algorithm>
#include <vector>

/**
 * Given a 0-indexed integer array nums of size n and two integers lower and upper, return the
 * number of fair pairs.
 *
 * A pair (i, j) is fair if:
 *
 * - 0 <= i < j < n, and
 *
 * - lower <= nums[i] + nums[j] <= upper
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums.length == n
 * ! -10^9 <= nums[i] <= 10^9
 * ! -10^9 <= lower <= upper <= 10^9
 */

class Solution {
public:
    long long countFairPairs(std::vector<int>& nums, int lower, int upper)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        long long result = 0;
        for (int j = 0; j < n; ++j) {
            auto iter1 = std::lower_bound(nums.begin(), nums.begin() + j, lower - nums[j]);
            auto iter2 = std::upper_bound(nums.begin(), nums.begin() + j, upper - nums[j]);
            result += iter2 - iter1;
        }
        return result;
    }
};