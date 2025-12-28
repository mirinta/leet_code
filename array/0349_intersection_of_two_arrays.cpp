#include <unordered_set>
#include <vector>

/**
 * Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in
 * the result must be unique and you may return the result in any order.
 *
 * ! 1 <= nums1.length, nums2.length <= 1000
 * ! 0 <= nums1[i], nums2[i] <= 1000
 */

class Solution {
public:
    std::vector<int> intersection(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> set2(nums2.begin(), nums2.end());
        std::vector<int> result;
        for (const auto& val : set2) {
            if (set1.count(val)) {
                result.push_back(val);
            }
        }
        return result;
    }
};