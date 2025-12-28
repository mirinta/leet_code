#include <unordered_map>
#include <vector>

/**
 * Given an array of integers nums and an integer k, return the total number of subarrays whose sum
 * equals to k.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! -1000 <= nums[i] <= 1000
 * ! -10^7 <= k <= 10^7
 */

class Solution {
public:
    int subarraySum(std::vector<int>& nums, int k)
    {
        // similar to LC 930
        // but the sliding window doesn't work because
        // there are negative number is nums that makes the sum
        // doesn't grow monotonically with the window size
        const int n = nums.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::unordered_map<int, int> map; // frequency of presum[x]
        map[0] = 1;                       // for cases that presum[i+1] - k = 0
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int target = presum[i + 1] - k;
            if (map.find(target) != map.end()) {
                result += map[target];
            }
            map[presum[i + 1]]++;
        }
        return result;
    }
};