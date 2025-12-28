#include <array>
#include <vector>

/**
 * Given an array of integers called nums, you can perform any of the following operation while nums
 * contains at least 2 elements:
 *
 * - Choose the first two elements of nums and delete them.
 *
 * - Choose the last two elements of nums and delete them.
 *
 * - Choose the first and the last elements of nums and delete them.
 *
 * The score of the operation is the sum of the deleted elements.
 *
 * Your task is to find the maximum number of operations that can be performed, such that all
 * operations have the same score.
 *
 * Return the maximum number of operations possible that satisfy the condition mentioned above.
 *
 * ! 2 <= nums.length <= 2000
 * ! 1 <= nums[i] <= 1000
 */

class Solution {
public:
    int maxOperations(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<std::vector<int>> memo(n, std::vector<int>(n, -1));
        int result = 1 + dp(memo, 2, n - 1, nums[0] + nums[1], nums);
        std::fill(memo.begin(), memo.end(), std::vector<int>(n, -1));
        result = std::max(result, 1 + dp(memo, 0, n - 3, nums[n - 1] + nums[n - 2], nums));
        std::fill(memo.begin(), memo.end(), std::vector<int>(n, -1));
        result = std::max(result, 1 + dp(memo, 1, n - 2, nums[0] + nums[n - 1], nums));
        return result;
    }

private:
    int dp(std::vector<std::vector<int>>& memo, int lo, int hi, int score, const std::vector<int>& nums)
    {
        if (hi - lo + 1 < 2)
            return 0;

        if (memo[lo][hi] != -1)
            return memo[lo][hi];

        int result = 0;
        if (nums[lo] + nums[lo + 1] == score) {
            result = std::max(result, 1 + dp(memo, lo + 2, hi, score, nums));
        }
        if (nums[hi] + nums[hi - 1] == score) {
            result = std::max(result, 1 + dp(memo, lo, hi - 2, score, nums));
        }
        if (nums[lo] + nums[hi] == score) {
            result = std::max(result, 1 + dp(memo, lo + 1, hi - 1, score, nums));
        }
        return memo[lo][hi] = result;
    }
};