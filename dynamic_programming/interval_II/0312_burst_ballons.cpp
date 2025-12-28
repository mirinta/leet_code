#include <vector>

/**
 * You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it
 * represented by an array nums. You are asked to burst all the balloons.
 *
 * If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or
 * i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on
 * it.
 *
 * Return the maximum coins you can collect by bursting the balloons wisely.
 *
 * ! n == nums.length
 * ! 1 <= n <= 300
 * ! 0 <= nums[i] <= 100
 */

class Solution {
public:
    int maxCoins(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        return dp(memo, 0, nums.size() - 1, nums);
    }

private:
    int dp(std::vector<std::vector<int>>& memo, int lo, int hi, const std::vector<int>& nums)
    {
        if (lo > hi)
            return 0;

        if (memo[lo][hi] != -1)
            return memo[lo][hi];

        const int n = nums.size();
        int result = 0;
        // select the last bursted balloon k in the range [lo:hi]
        for (int i = lo; i <= hi; ++i) {
            int score = nums[i] * (hi + 1 >= n ? 1 : nums[hi + 1]) * (lo - 1 < 0 ? 1 : nums[lo - 1]);
            score += dp(memo, lo, i - 1, nums) + dp(memo, i + 1, hi, nums);
            result = std::max(result, score);
        }
        return memo[lo][hi] = result;
    }
};