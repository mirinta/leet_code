#include <algorithm>
#include <vector>

/**
 * You are given a 0-indexed array nums consisting of positive integers.
 *
 * Initially, you can increase the value of any element in the array by at most 1.
 *
 * After that, you need to select one or more elements from the final array such that those elements
 * are consecutive when sorted in increasing order. For example, the elements [3, 4, 5] are
 * consecutive while [3, 4, 6] and [1, 1, 2, 3] are not.
 *
 * Return the maximum number of elements that you can select.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^6
 */

class Solution {
public:
    int maxSelectedElements(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        // dp[i] = max num of consecutive numbers ending at i
        int dp[1000002];
        std::memset(dp, 0, sizeof(dp));
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int val = nums[i];
            dp[val + 1] = std::max(dp[val + 1], dp[val] + 1);
            dp[val] = std::max(dp[val], dp[val - 1] + 1);
            result = std::max({result, dp[val + 1], dp[val]});
        }
        return result;
    }
};