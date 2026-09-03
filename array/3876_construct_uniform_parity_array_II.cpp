#include <algorithm>
#include <vector>

/**
 * You are given an array nums1 of n distinct integers.
 *
 * You want to construct another array nums2 of length n such that the elements in nums2 are either all odd or all even.
 *
 * For each index i, you must choose exactly one of the following (in any order):
 *
 * - nums2[i] = nums1[i]​​​​​​​
 *
 * - nums2[i] = nums1[i] - nums1[j], for an index j != i, such that nums1[i] - nums1[j] >= 1
 *
 * Return true if it is possible to construct such an array, otherwise return false.
 *
 * ! 1 <= n == nums1.length <= 10^5
 * ! 1 <= nums1[i] <= 10^9
 * ! nums1 consists of distinct integers.
 */

class Solution {
public:
    bool uniformArray(std::vector<int>& nums1)
    {
        return approach2(nums1);
    }

private:
    bool approach2(std::vector<int>& nums1)
    {
        const int n = nums1.size();
        int minOdd = INT_MAX;
        for (const auto& val : nums1) {
            if (val % 2) {
                minOdd = std::min(minOdd, val);
            }
        }
        bool case0 = true;
        bool case1 = true;
        for (int i = 0, odd = 0; i < n; ++i) {
            const bool isOdd = nums1[i] % 2;
            case0 &= !isOdd || (minOdd != INT_MAX && minOdd < nums1[i]);
            case1 &= isOdd || (minOdd != INT_MAX && minOdd < nums1[i]);
        }
        return case0 || case1;
    }

    bool approach1(std::vector<int>& nums1)
    {
        const int n = nums1.size();
        std::sort(nums1.begin(), nums1.end());
        bool case0 = true;
        bool case1 = true;
        for (int i = 0, odd = 0; i < n; ++i) {
            const bool isOdd = nums1[i] % 2;
            case0 &= !isOdd || odd > 0;
            case1 &= isOdd || odd > 0;
            odd += isOdd;
        }
        return case0 || case1;
    }
};