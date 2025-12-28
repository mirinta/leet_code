#include <vector>

/**
 * You are given an integer array nums of size n. For each index i where 0 <= i < n, define a
 * subarray nums[start ... i] where start = max(0, i - nums[i]).
 *
 * Return the total sum of all elements from the subarray defined for each index in the array.
 *
 * ! 1 <= n == nums.length <= 100
 * ! 1 <= nums[i] <= 1000
 */

class Solution {
public:
    int subarraySum(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> presum(n + 1);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        auto query = [&](int l, int r) { return presum[r + 1] - presum[l]; };
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result += query(std::max(0, i - nums[i]), i);
        }
        return result;
    }
};
