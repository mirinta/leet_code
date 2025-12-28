#include <vector>

/**
 * Given an integer array arr and an integer k, modify the array by repeating it k times.
 *
 * For example, if arr = [1, 2] and k = 3 then the modified array will be [1, 2, 1, 2, 1, 2].
 *
 * Return the maximum sub-array sum in the modified array. Note that the length of the sub-array can
 * be 0 and its sum in that case is 0.
 *
 * As the answer can be very large, return the answer modulo 109 + 7.
 *
 * ! 1 <= arr.length <= 10^5
 * ! 1 <= k <= 10^5
 * ! -10^4 <= arr[i] <= 10^4
 */

class Solution {
public:
    int kConcatenationMaxSum(std::vector<int>& arr, int k)
    {
        // consider the pattern of the final answer:
        // FRONT arr arr arr arr ... arr TAIL, where FRONT and TAIL are subarrays of arr
        //       |<--M = num of arrs-->|
        // if sum of arr[0:n-1] > 0, then M = k-2
        // otherwise, M = 0
        if (k == 1)
            return maxSubarraySum(arr) % kMod;

        long long sum = 0;
        for (const auto& val : arr) {
            sum = (sum + val) % kMod;
        }
        arr.insert(arr.end(), arr.begin(), arr.end());
        const long long frontAndTail = maxSubarraySum(arr) % kMod;
        if (sum < 0 || k == 2)
            return frontAndTail;

        return (sum * (k - 2) % kMod + frontAndTail) % kMod;
    }

private:
    static constexpr int kMod = 1e9 + 7;

    long long maxSubarraySum(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<long long> dp(n + 1);
        long long result = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = std::max<long long>(nums[i - 1], (nums[i - 1] + dp[i - 1]));
            result = std::max(result, dp[i]);
        }
        return result;
    }
};