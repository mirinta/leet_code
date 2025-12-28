#include <unordered_map>
#include <vector>

/**
 * Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that
 * the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.
 *
 * Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.
 *
 * A subarray is defined as a contiguous block of elements in the array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= p <= 10^9
 */

class Solution {
public:
    int minSubarray(std::vector<int>& nums, int p)
    {
        // (total - sum) % p = 0
        // total % p = sum % p
        // let presum[i] = sum of nums[0:i]
        // if nums[j+1:i] is a valid subarray
        // then (presum[i] - presum[j]) % p = total % p
        // presum[j] % p = (presum[i] - total) % p
        const int n = nums.size();
        int total = 0;
        for (const auto& val : nums) {
            total = (total + val) % p;
        }
        if (total == 0)
            return 0;

        std::unordered_map<int, int> map;
        map[0] = -1;
        int result = n;
        for (int i = 0, presum = 0; i < n; ++i) {
            presum = (presum + nums[i]) % p;
            const int target = (presum - total + p) % p;
            if (map.count(target)) {
                result = std::min(result, i - map[target]);
            }
            map[presum] = i;
        }
        return result == n ? -1 : result;
    }
};