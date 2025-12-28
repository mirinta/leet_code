#include <algorithm>
#include <unordered_set>
#include <vector>

/**
 * You are given two 0-indexed integer arrays nums1 and nums2 of even length n.
 *
 * You must remove n / 2 elements from nums1 and n / 2 elements from nums2. After the removals, you
 * insert the remaining elements of nums1 and nums2 into a set s.
 *
 * Return the maximum possible size of the set s.
 *
 * ! n == nums1.length == nums2.length
 * ! 1 <= n <= 2 * 10^4
 * ! n is even.
 * ! 1 <= nums1[i], nums2[i] <= 10^9
 */

class Solution {
public:
    int maximumSetSize(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int n = nums1.size();
        std::unordered_set<int> set1(nums1.begin(), nums1.end());
        std::unordered_set<int> set2(nums2.begin(), nums2.end());
        int unique1 = set1.size(); // remove duplicates from nums1
        int unique2 = set2.size(); // remove duplicates from nums2
        int intersection =
            std::count_if(set1.begin(), set1.end(), [&set2](const auto& val) { return set2.count(val); });
        // we need to remove more elements from unique1
        if (const int extra1 = unique1 - n / 2; extra1 > 0) {
            // remove elements from intersection as much as possible
            intersection = std::max(0, intersection - extra1);
            unique1 -= extra1;
        }
        // we need to remove more elements from unique2
        if (const int extra2 = unique2 - n / 2; extra2 > 0) {
            // remove elements from intersection as much as possible
            intersection = std::max(0, intersection - extra2);
            unique2 -= extra2;
        }
        return unique1 + unique2 - intersection; // |A∪B| = |A| + |B| - |A∩B|
    }
};