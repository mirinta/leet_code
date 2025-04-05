#include <vector>

/**
 * You are given a 0-indexed integer array nums.
 *
 * Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such
 * triplets have a negative value, return 0.
 *
 * The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
 *
 * ! 3 <= nums.length <= 100
 * ! 1 <= nums[i] <= 10^6
 */

class Solution
{
public:
    long long maximumTripletValue(std::vector<int>& nums)
    {
        // prefixMax[i] = max value of nums[0:i]
        // suffixMax[i] = max value of nums[i:n-1]
        const int n = nums.size();
        std::vector<int> prefixMax(n, INT_MIN);
        std::vector<int> suffixMax(n, INT_MIN);
        for (int i = 0; i < n; ++i) {
            prefixMax[i] = std::max(i > 0 ? prefixMax[i - 1] : INT_MIN, nums[i]);
            suffixMax[n - i - 1] = std::max(i > 0 ? suffixMax[n - i] : INT_MIN, nums[n - i - 1]);
        }
        long long result = 0;
        for (int j = 1; j < n - 1; ++j) {
            result = std::max(result, 1LL * (prefixMax[j - 1] - nums[j]) * suffixMax[j + 1]);
        }
        return result;
    }
};
