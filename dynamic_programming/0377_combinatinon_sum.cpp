#include <vector>

/**
 * Given an array of distinct integers nums and a target integer target, return the number of
 * possible combinations that add up to target.
 *
 * The test cases are generated so that the answer can fit in a 32-bit integer.
 *
 * ! 1 <= nums.length <= 200
 * ! 1 <= nums[i] <= 1000
 * ! All the elements of nums are unique.
 * ! 1 <= target <= 1000
 */

class Solution {
public:
    int combinationSum4(std::vector<int>& nums, int target)
    {
        // similar to "climbing stairs"
        // height is "target" and elements of nums are choices of steps
        // dp[i] = num of ways to make up i
        std::vector<size_t> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i) {
            for (const auto& val : nums) {
                if (val > i)
                    continue;

                dp[i] += dp[i - val];
            }
        }
        return dp[target];
    }
};