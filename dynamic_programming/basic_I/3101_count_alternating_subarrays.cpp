#include <vector>

/**
 * You are given a binary array nums.
 *
 * We call a subarray alternating if no two adjacent elements in the subarray have the same value.
 *
 * Return the number of alternating subarrays in nums.
 *
 * ! 1 <= nums.length <= 10^5
 * ! nums[i] is either 0 or 1.
 */

class Solution {
public:
    long long countAlternatingSubarrays(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    long long approach2(const std::vector<int>& nums)
    {
        const int n = nums.size();
        long long count = 0;
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                count = 1;
            } else {
                count++;
            }
            result += count;
        }
        return result;
    }

    long long approach1(const std::vector<int>& nums)
    {
        // dp[i] = num of alternating subarrays of nums[0:i] ending at nums[i]
        const int n = nums.size();
        std::vector<long long> dp(n);
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            if (i > 0 && nums[i] != nums[i - 1]) {
                dp[i] += dp[i - 1];
            }
            result += dp[i];
        }
        return result;
    }
};