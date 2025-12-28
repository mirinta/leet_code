#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums. You want to maximize the number of points you get by
 * performing the following operation any number of times:
 *
 * - Pick any nums[i] and delete it to earn nums[i] points. Afterwards, you must delete every
 * element equal to nums[i] - 1 and every element equal to nums[i] + 1.
 *
 * Return the maximum number of points you can earn by applying the above operation some number of
 * times.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! 1 <= nums[i] <= 10^4
 */

class Solution {
public:
    int deleteAndEarn(std::vector<int>& nums)
    {
        return approach2(nums);
    }

private:
    int approach2(std::vector<int>& nums)
    {
        // DP with space optimization
        std::unordered_map<int, int> points; // val to frequency*val
        int maxElement = 0;
        for (const auto& val : nums) {
            maxElement = std::max(maxElement, val);
            points[val] += val;
        }
        int robbed = INT_MIN;
        int notRobbed = 0;
        for (int i = 1; i <= maxElement; ++i) {
            const int temp = notRobbed;
            notRobbed = std::max(robbed, notRobbed);
            robbed = temp + points[i];
        }
        return std::max(notRobbed, robbed);
    }

    int approach1(std::vector<int>& nums)
    {
        // let count[j] to be the number of nums[i]=j
        // - if we pick nums[i]=j, we earn j*count[j] points
        // - all nums[i]-1 are deleted, i.e., count[j-1]=0
        // - all nums[i]+1 are deleted, i.e., count[j+1]=0
        // this is similar to the House Robber problem:
        // - if we rob house[j] in this round,
        //   then house[j-1] and house[j+1] can't be robbed in the next round
        std::unordered_map<int, int> points; // val to frequency*val
        int maxElement = 0;
        for (const auto& val : nums) {
            maxElement = std::max(maxElement, val);
            points[val] += val;
        }
        // dp[i][0] = max value of robbing the first i houses and the ith house is not robbed
        // dp[i][1] = max value of robbing the first i houses and the ith house is robbed
        std::vector<std::vector<int>> dp(maxElement + 1, std::vector<int>(2, 0));
        dp[0][1] = INT_MIN;
        for (int i = 1; i <= maxElement; ++i) {
            dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0] + points[i];
        }
        return std::max(dp[maxElement][0], dp[maxElement][1]);
    }
};