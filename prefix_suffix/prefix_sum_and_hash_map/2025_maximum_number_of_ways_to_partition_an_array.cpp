#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed integer array nums of length n. The number of ways to partition nums is
 * the number of pivot indices that satisfy both conditions:
 *
 * - 1 <= pivot < n
 *
 * - nums[0] + nums[1] + ... + nums[pivot - 1] == nums[pivot] + nums[pivot + 1] + ... + nums[n - 1]
 * You are also given an integer k.
 *
 * You can choose to change the value of one element of nums to k, or to leave the array unchanged.
 *
 * Return the maximum possible number of ways to partition nums to satisfy both conditions after
 * changing at most one element.
 *
 * ! n == nums.length
 * ! 2 <= n <= 10^5
 * ! -10^5 <= k, nums[i] <= 10^5
 */

class Solution {
public:
    int waysToPartition(std::vector<int>& nums, int k)
    {
        // partition index = i
        // [0...i][i+1...n-1]
        // since we want two non-empty subarrays, then 0 <= i < n-1
        const int n = nums.size();
        std::vector<long long> prefixSum(n);
        std::vector<long long> suffixSum(n);
        prefixSum[0] = nums[0];
        suffixSum[n - 1] = nums[n - 1];
        for (int i = 1; i < n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
            suffixSum[n - i - 1] = suffixSum[n - i] + nums[n - i - 1];
        }
        const long long total = prefixSum[n - 1];
        // case 1: all elements are not changed
        int unchanged = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (prefixSum[i] == total - prefixSum[i]) {
                unchanged++;
            }
        }
        // case 2: nums[i] is changed
        std::vector<int> changed(n);
        // case 2.1: count the num of partition indices < i
        // prefixSum[0:i-1] does not changed
        std::unordered_map<long long, int> map;
        for (int i = 0; i < n; ++i) {
            const long long newTotal = total - nums[i] + k;
            if (newTotal % 2 == 0) {
                changed[i] += map[newTotal / 2];
            }
            map[prefixSum[i]]++;
        }
        // case 2.2: count the num of valid partition indices > i
        // suffixSum[n-1:i-1] does not changed
        map.clear();
        for (int i = n - 1; i >= 0; --i) {
            const long long newTotal = total - nums[i] + k;
            if (newTotal % 2 == 0) {
                changed[i] += map[newTotal / 2];
            }
            map[suffixSum[i]]++;
        }
        return std::max(unchanged, *std::max_element(changed.begin(), changed.end()));
    }
};