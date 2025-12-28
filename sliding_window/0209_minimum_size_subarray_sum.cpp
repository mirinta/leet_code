#include <vector>

/**
 * Given an array of positive integers nums and a positive integer target, return the minimal length
 * of a subarray whose sum is greater than or equal to target. If there is no such subarray, return
 * 0 instead.
 *
 * ! 1 <= target <= 10^9
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^4
 */

class Solution {
public:
    int minSubArrayLen(int target, std::vector<int>& nums)
    {
        return approach2(target, nums);
    }

private:
    // sliding window, TC = O(N), SC = O(1)
    int approach2(int target, const std::vector<int>& nums)
    {
        const int n = nums.size();
        int sum = 0;
        int result = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                sum -= nums[left];
                result = std::min(result, right - left + 1);
                left++;
            }
        }
        return result == INT_MAX ? 0 : result;
    }

    // prefix sum + binary search, TC = O(NlogN), SC = O(N)
    int approach1(int target, const std::vector<int>& nums)
    {
        // let presum[i] = sum of nums[0:i-1]
        // if sum of nums[j:i] >= target,
        // then presum[i+1] - presum[j] >= target
        const int n = nums.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        int result = INT_MAX;
        for (int j = 0; j < n; ++j) {
            auto iter = std::lower_bound(presum.begin(), presum.end(), target + presum[j]);
            if (iter != presum.end()) {
                const int iPlus1 = iter - presum.begin();
                result = std::min(result, iPlus1 - j);
            }
        }
        return result == INT_MAX ? 0 : result;
    }
};