#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the number of non-empty subarrays that have
 * a sum divisible by k.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! -10^4 <= nums[i] <= 10^4
 * ! 2 <= k <= 10^4
 */

class Solution {
public:
    int subarraysDivByK(std::vector<int>& nums, int k)
    {
        // let sum[i] = sum of nums[0:i]
        // if nums[j+1:i] is a valid subarray
        // then (sum[i] - sum[j]) % k = 0
        // then sum[i] % k = sum[j] % k
        const int n = nums.size();
        std::unordered_map<int, int> map;
        // base case: nums[0:i] is a valid subarray
        // sum[i] % k = 0
        map[0] = 1;
        int result = 0;
        for (int i = 0, sum = 0; i < n; ++i) {
            sum += nums[i];
            const int target = (sum % k + k) % k; // prevent negative values
            result += map[target];
            map[target]++;
        }
        return result;
    }
};