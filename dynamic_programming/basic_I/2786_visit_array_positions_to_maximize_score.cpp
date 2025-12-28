#include <array>
#include <vector>

/**
 * You are given a 0-indexed integer array nums and a positive integer x.
 *
 * You are initially at position 0 in the array and you can visit other positions according to the
 * following rules:
 *
 * - If you are currently in position i, then you can move to any position j such that i < j.
 *
 * - For each position i that you visit, you get a score of nums[i].
 *
 * - If you move from a position i to a position j and the parities of nums[i] and nums[j] differ,
 * then you lose a score of x. Return the maximum total score you can get.
 *
 * Note that initially you have nums[0] points.
 *
 * ! 2 <= nums.length <= 10^5
 * ! 1 <= nums[i], x <= 10^6
 */

class Solution {
public:
    long long maxScore(std::vector<int>& nums, int x)
    {
        return approach3(nums, x);
    }

private:
    long long approach3(const std::vector<int>& nums, int x)
    {
        const int n = nums.size();
        long long even = LLONG_MIN / 2;
        long long odd = LLONG_MIN / 2;
        if (nums[0] % 2) {
            odd = nums[0];
        } else {
            even = nums[0];
        }
        for (int i = 1; i < n; ++i) {
            if (nums[i] % 2) {
                odd = std::max({odd, odd + nums[i], even + nums[i] - x});
            } else {
                even = std::max({even, even + nums[i], odd + nums[i] - x});
            }
        }
        return std::max(odd, even);
    }

    long long approach2(const std::vector<int>& nums, int x)
    {
        // dp[i][0] = max score of nums[0:i] while the last picked element is even
        // dp[i][1] = max score of nums[0:i] while the last picked element is odd
        const int n = nums.size();
        std::vector<std::array<long long, 2>> dp(n, {LLONG_MIN / 2, LLONG_MIN / 2});
        dp[0][nums[0] % 2] = nums[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = dp[i - 1]; // nums[i] is not picked
            if (nums[i] % 2) {
                dp[i][1] = std::max({dp[i][1], dp[i - 1][1] + nums[i], dp[i - 1][0] + nums[i] - x});
            } else {
                dp[i][0] = std::max({dp[i][0], dp[i - 1][0] + nums[i], dp[i - 1][1] + nums[i] - x});
            }
        }
        return std::max(dp[n - 1][0], dp[n - 1][1]);
    }

    long long approach1(const std::vector<int>& nums, int x)
    {
        const int n = nums.size();
        std::vector<std::array<long long, 2>> memo(n, {-1, -1});
        return nums[0] + solve(memo, 1, nums[0] % 2, x, nums);
    }

    long long
        solve(std::vector<std::array<long long, 2>>& memo, int i, bool prevIsOdd, int x, const std::vector<int>& nums)
    {
        if (i == nums.size())
            return 0;

        if (memo[i][prevIsOdd] != -1)
            return memo[i][prevIsOdd];

        const long long case1 = solve(memo, i + 1, prevIsOdd, x, nums);
        const bool currIsOdd = nums[i] % 2;
        const long long case2 = nums[i] + solve(memo, i + 1, currIsOdd, x, nums) - (currIsOdd ^ prevIsOdd) * x;
        return memo[i][prevIsOdd] = std::max(case1, case2);
    }
};