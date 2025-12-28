#include <unordered_map>
#include <vector>

/**
 * You are given 2 integer arrays nums1 and nums2 of lengths n and m respectively. You are also
 * given a positive integer k.
 *
 * A pair (i, j) is called good if nums1[i] is divisible by nums2[j] * k (0 <= i <= n - 1, 0 <= j <=
 * m - 1).
 *
 * Return the total number of good pairs.
 *
 * ! 1 <= n, m <= 10^5
 * ! 1 <= nums1[i], nums2[j] <= 10^6
 * ! 1 <= k <= 10^3
 */

class Solution {
public:
    long long numberOfPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        std::unordered_map<int, long long> map1;
        int max = INT_MIN;
        for (const auto& val : nums1) {
            map1[val]++;
            max = std::max(max, val);
        }
        std::unordered_map<int, long long> map2;
        for (const auto& val : nums2) {
            map2[val]++;
        }
        long long result = 0;
        for (const auto& [val2, freq] : map2) {
            for (int val1 = val2 * k; val1 <= max; val1 += val2 * k) {
                if (map1.count(val1)) {
                    result += freq * map1[val1];
                }
            }
        }
        return result;
    }
};