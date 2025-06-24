#include <vector>

/**
 * You are given a 0-indexed integer array nums and two integers key and k. A k-distant index is an
 * index i of nums for which there exists at least one index j such that |i - j| <= k and nums[j] ==
 * key.
 *
 * Return a list of all k-distant indices sorted in increasing order.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 * ! key is an integer from the array nums.
 * ! 1 <= k <= nums.length
 */

class Solution
{
public:
    std::vector<int> findKDistantIndices(std::vector<int>& nums, int key, int k)
    {
        const int n = nums.size();
        std::vector<int> result;
        for (int i = 0, right = 0; i < n; ++i) {
            if (nums[i] != key)
                continue;

            const int left = std::max(right, i - k);
            right = std::min(n, i + k + 1);
            for (int j = left; j < right; ++j) {
                result.push_back(j);
            }
        }
        return result;
    }
};
