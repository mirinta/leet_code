#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the number of good subarrays of nums.
 *
 * A subarray arr is good if it there are at least k pairs of indices (i, j) such that i < j and
 * arr[i] == arr[j].
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i], k <= 10^9
 */

class Solution {
public:
    long long countGood(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, long long> map;
        long long pairs = 0;
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            pairs += map[nums[right]]++;
            while (pairs >= k) {
                pairs -= --map[nums[left]];
                left++;
            }
            result += left;
        }
        return result;
    }
};
