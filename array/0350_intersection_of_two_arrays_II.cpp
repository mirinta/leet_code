#include <unordered_map>
#include <vector>

/**
 * Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in
 * the result must appear as many times as it shows in both arrays and you may return the result in
 * any order.
 *
 * ! 1 <= nums1.length, nums2.length <= 1000
 * ! 0 <= nums1[i], nums2[i] <= 1000
 */

class Solution {
public:
    std::vector<int> intersect(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums1) {
            map[val]++;
        }
        std::vector<int> result;
        for (const auto& val : nums2) {
            if (map[val] > 0) {
                map[val]--;
                result.push_back(val);
            }
        }
        return result;
    }
};