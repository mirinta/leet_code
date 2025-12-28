#include <vector>

/**
 * You are given a 0-indexed array nums of integers.
 *
 * A triplet of indices (i, j, k) is a mountain if:
 *
 * - i < j < k
 *
 * - nums[i] < nums[j] and nums[k] < nums[j]
 *
 * Return the minimum possible sum of a mountain triplet of nums. If no such triplet exists, return
 * -1.
 *
 * ! 3 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^8
 */

class Solution {
public:
    int minimumSum(std::vector<int>& nums)
    {
        const int n = nums.size();
        if (n < 3)
            return false;

        // prefixMin[i] = min of nums[0:i]
        std::vector<int> prefixMin(n, nums[0]);
        for (int i = 1; i < n; ++i) {
            prefixMin[i] = std::min(prefixMin[i - 1], nums[i]);
        }
        // suffix[i] = min of nums[i:n-1]
        std::vector<int> suffixMin(n, nums[n - 1]);
        for (int i = n - 2; i >= 0; --i) {
            suffixMin[i] = std::min(suffixMin[i + 1], nums[i]);
        }
        int result = INT_MAX;
        for (int i = 1; i < n - 1; ++i) {
            if (prefixMin[i] == nums[i] || suffixMin[i] == nums[i])
                continue;

            result = std::min(result, nums[i] + prefixMin[i] + suffixMin[i]);
        }
        return result == INT_MAX ? -1 : result;
    }
};