#include <unordered_map>
#include <vector>

/**
 * You are given an array nums consisting of positive integers.
 *
 * A special subsequence is defined as a subsequence of length 4, represented by indices (p, q, r,
 * s), where p < q < r < s. This subsequence must satisfy the following conditions:
 *
 * - nums[p] * nums[r] == nums[q] * nums[s]
 *
 * - There must be at least one element between each pair of indices. In other words, q - p > 1, r -
 * q > 1 and s - r > 1.
 *
 * Return the number of different special subsequences in nums.
 *
 * ! 7 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 */

class Solution
{
public:
    long long numberOfSubsequences(std::vector<int>& nums)
    {
        // 0 <= p < q < r < s <= n-1
        // q - p >= 2
        // r - q >= 2
        // s - r >= 2
        // ------
        // nums[p] / nums[q] = nums[s] / nums[r]
        const int n = nums.size();
        std::unordered_map<double, long long> map;
        long long result = 0;
        for (int r = 4; r + 2 < n; ++r) {
            const int q = r - 2;
            for (int p = q - 2; p >= 0; --p) {
                map[1.0 * nums[p] / nums[q]]++;
            }
            for (int s = r + 2; s < n; ++s) {
                result += map[1.0 * nums[s] / nums[r]];
            }
        }
        return result;
    }
};
