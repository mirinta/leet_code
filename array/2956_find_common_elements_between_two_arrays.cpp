#include <unordered_set>
#include <vector>

/**
 * You are given two 0-indexed integer arrays nums1 and nums2 of sizes n and m, respectively.
 *
 * Consider calculating the following values:
 *
 * - The number of indices i such that 0 <= i < n and nums1[i] occurs at least once in nums2.
 *
 * - The number of indices i such that 0 <= i < m and nums2[i] occurs at least once in nums1.
 *
 * - Return an integer array answer of size 2 containing the two values in the above order.
 *
 * ! n == nums1.length
 * ! m == nums2.length
 * ! 1 <= n, m <= 100
 * ! 1 <= nums1[i], nums2[i] <= 100
 */

class Solution {
public:
    std::vector<int> findIntersectionValues(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> set2(nums2.begin(), nums2.end());
        return {helper(nums1, set2), helper(nums2, set1)};
    }

private:
    int helper(const std::vector<int>& nums, const std::unordered_set<int>& set)
    {
        int count = 0;
        for (const auto& val : nums) {
            if (set.count(val)) {
                count++;
            }
        }
        return count;
    }
};