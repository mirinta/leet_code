#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and two positive integers m and k.
 *
 * Return the maximum sum out of all almost unique subarrays of length k of nums. If no such
 * subarray exists, return 0.
 *
 * A subarray of nums is almost unique if it contains at least m distinct elements.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 2 * 10^4
 * ! 1 <= m <= k <= nums.length
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long maxSum(std::vector<int>& nums, int m, int k)
    {
        const int n = nums.size();
        std::unordered_map<int, int> map;
        long long sum = 0;
        long long result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            map[nums[right]]++;
            if (right - left + 1 > k) {
                sum -= nums[left];
                if (--map[nums[left]] == 0) {
                    map.erase(nums[left]);
                }
                left++;
            }
            if (map.size() >= m) {
                result = std::max(result, sum);
            }
        }
        return result;
    }
};