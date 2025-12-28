#include <unordered_map>
#include <vector>

/**
 * You are given two integer arrays nums1 and nums2 where nums2 is an anagram of nums1. Both arrays
 * may contain duplicates.
 *
 * Return an index mapping array mapping from nums1 to nums2 where mapping[i] = j means the ith
 * element in nums1 appears in nums2 at index j. If there are multiple answers, return any of them.
 *
 * An array a is an anagram of an array b means b is made by randomizing the order of the elements
 * in a.
 *
 * ! 1 <= nums1.length <= 100
 * ! nums2.length == nums1.length
 * ! 0 <= nums1[i], nums2[i] <= 10^5
 * ! nums2 is an anagram of nums1.
 */

class Solution {
public:
    std::vector<int> anagramMappings(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int n = nums1.size();
        std::unordered_map<int, int> map; // value to index
        for (int i = 0; i < n; ++i) {
            map[nums2[i]] = i;
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            result[i] = map[nums1[i]];
        }
        return result;
    }
};