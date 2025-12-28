#include <unordered_map>
#include <vector>

/**
 * Given an integer array nums and an integer k, return the maximum length of a subarray that sums
 * to k. If there is not one, return 0 instead.
 *
 * ! 1 <= nums.length <= 2 * 10^5
 * ! -10^4 <= nums[i] <= 10^4
 * ! -10^9 <= k <= 10^9
 */

class Solution {
public:
    int maxSubArrayLen(std::vector<int>& nums, int k)
    {
        // sum[i] = sum of nums[0:i]
        // if nums[j+1:i] is a valid subarray, then sum[i] - sum[j] = k
        //
        // find the smallest j such that sum[j] = sum[i] - k
        // length of this subarray = i-j
        //
        // corner case: nums[0:i] is a valid subarray
        // sum[i] = k, it means sum[j] = 0
        // length = i+1 = i-j, then j = -1
        const int n = nums.size();
        std::unordered_map<long long, int> map;
        map[0] = -1;
        long long sum = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            const long long target = sum - k;
            if (map.count(target)) {
                result = std::max(result, i - map[target]);
            }
            if (!map.count(sum)) {
                map[sum] = i;
            }
        }
        return result;
    }
};
