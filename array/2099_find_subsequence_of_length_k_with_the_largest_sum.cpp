#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums and an integer k. You want to find a subsequence of nums of
 * length k that has the largest sum.
 *
 * Return any such subsequence as an integer array of length k.
 *
 * A subsequence is an array that can be derived from another array by deleting some or no elements
 * without changing the order of the remaining elements.
 *
 * ! 1 <= nums.length <= 1000
 * ! -10^5 <= nums[i] <= 10^5
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    std::vector<int> maxSubsequence(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::vector<std::pair<int, int>> pairs;
        pairs.reserve(n);
        for (int i = 0; i < n; ++i) {
            pairs.emplace_back(i, nums[i]);
        }
        std::sort(pairs.begin(), pairs.end(), [](const auto& p1, const auto& p2) { return p1.second > p2.second; });
        std::sort(pairs.begin(), pairs.begin() + k, [](const auto& p1, const auto& p2) { return p1.first < p2.first; });
        std::vector<int> result(k);
        for (int i = 0; i < k; ++i) {
            result[i] = pairs[i].second;
        }
        return result;
    }
};
