#include <vector>

/**
 * You are given a 0-indexed integer array nums, where nums[i] is a digit between 0 and 9
 * (inclusive).
 *
 * The triangular sum of nums is the value of the only element present in nums after the following
 * process terminates:
 *
 * 1. Let nums comprise of n elements. If n == 1, end the process. Otherwise, create a new 0-indexed
 * integer array newNums of length n - 1.
 *
 * 2. For each index i, where 0 <= i < n - 1, assign the value of newNums[i] as (nums[i] +
 * nums[i+1]) % 10, where % denotes modulo operator.
 *
 * 3. Replace the array nums with newNums.
 *
 * 4. Repeat the entire process starting from step 1.
 *
 * Return the triangular sum of nums.
 *
 * ! 1 <= nums.length <= 1000
 * ! 0 <= nums[i] <= 9
 */

class Solution
{
public:
    int triangularSum(std::vector<int>& nums)
    {
        static constexpr int kMod = 10;
        const int n = nums.size();
        std::vector<std::vector<int>> combo(n + 1, std::vector<int>(n + 1, 0));
        for (int i = 0; i <= n; ++i) {
            combo[i][0] = 1;
            combo[i][i] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                combo[i][j] = (combo[i - 1][j] + combo[i - 1][j - 1]) % kMod;
            }
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            result = (result + nums[i] * combo[n - 1][i] % kMod) % kMod;
        }
        return result;
    }
};
