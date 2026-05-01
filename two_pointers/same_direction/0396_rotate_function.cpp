#include <numeric>
#include <vector>

/**
 * You are given an integer array nums of length n.
 *
 * Assume arrk to be an array obtained by rotating nums by k positions clock-wise. We define the rotation function F on
 * nums as follows:
 *
 * - F(k) = 0 * arrk[0] + 1 * arrk[1] + ... + (n - 1) * arrk[n - 1]
 *
 * Return the maximum value of F(0), F(1), ..., F(n - 1).
 *
 * The test cases are generated so the the answer fits in a 32-bit integer.
 *
 * ! n == nums.length
 * ! 1 <= n <= 10^5
 * ! -100 <= nums[i] <= 100
 */

class Solution {
public:
    int maxRotateFunction(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int result = INT_MIN;
        for (int i = 0, f = 0; i < 2 * n - 1; ++i) {
            if (i < n) {
                f += i * nums[i];
            } else {
                f += n * nums[i - n] - sum;
            }
            if (i >= n - 1) {
                result = std::max(result, f);
            }
        }
        return result;
    }
};