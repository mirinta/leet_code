#include <unordered_map>
#include <vector>

/**
 * You are given an array nums of length n and a positive integer k.
 *
 * A subarray of nums is called good if the absolute difference between its first and last element
 * is exactly k, in other words, the subarray nums[i..j] is good if |nums[i] - nums[j]| == k.
 *
 * Return the maximum sum of a good subarray of nums. If there are no good subarrays, return 0.
 *
 * ! 2 <= nums.length <= 10^5
 * ! -10^9 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^9
 */

class Solution {
public:
    long long maximumSubarraySum(std::vector<int>& nums, int k)
    {
        // given index j, we need to find index i
        // such that i <= j and nums[i] = nums[j] +/- k
        // let presum[i] = sum of nums[0:i-1]
        // score = sum of nums[i:j] = presum[j+1] - presum[i]
        // since j is fixed, we need min of presum[i] to maximize score
        const int n = nums.size();
        std::vector<long long> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::unordered_map<int, long long> map; // <nums[i], min of presum[i]>
        long long result = LLONG_MIN;
        for (int j = 0; j < n; ++j) {
            for (const auto& val : {nums[j] + k, nums[j] - k}) {
                if (map.find(val) == map.end())
                    continue;

                result = std::max(result, presum[j + 1] - map[val]);
            }
            if (map.find(nums[j]) == map.end()) {
                map[nums[j]] = presum[j];
            } else {
                map[nums[j]] = std::min(map[nums[j]], presum[j]);
            }
        }
        return result == LLONG_MIN ? 0 : result;
    }
};