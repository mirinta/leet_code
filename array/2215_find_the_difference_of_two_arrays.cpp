#include <unordered_set>
#include <vector>

/**
 * Given two 0-indexed integer arrays "nums1" and "nums2", return a list "answer" of size 2 where:
 *
 * - answer[0] is a list of all distinct integers in "nums1" which are not present in "nums2".
 *
 * - answer[1] is a list of all distinct integers in "nums2" which are not present in "nums1".
 *
 * Note that the integers in the lists may be returned in any order.
 */

class Solution {
public:
    std::vector<std::vector<int>> findDifference(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> set2(nums2.begin(), nums2.end());
        std::vector<int> vec1;
        for (const auto& v1 : set1) {
            if (!set2.count(v1)) {
                vec1.push_back(v1);
            }
        }
        std::vector<int> vec2;
        for (const auto& v2 : set2) {
            if (!set1.count(v2)) {
                vec2.push_back(v2);
            }
        }
        return {vec1, vec2};
    }
};