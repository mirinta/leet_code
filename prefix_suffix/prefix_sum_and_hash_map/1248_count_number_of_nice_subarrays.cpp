#include <unordered_map>
#include <vector>

/**
 * Given an array of integers nums and an integer k. A continuous subarray is called nice if there
 * are k odd numbers on it.
 *
 * Return the number of nice sub-arrays.
 *
 * ! 1 <= nums.length <= 50000
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= k <= nums.length
 */

class Solution {
public:
    int numberOfSubarrays(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // sliding window, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums, int k)
    {
        return helper(nums, k) - helper(nums, k - 1);
    }

    // num of subarrays that each subarray contains at most k odd numbers
    int helper(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int result = 0;
        for (int left = 0, right = 0, count = 0; right < n; ++right) {
            count += nums[right] % 2;
            while (count > k) {
                count -= nums[left] % 2;
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }

    // prefix sum + hash map, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums, int k)
    {
        // let count[i] = num of odd numbers in nums[0:i]
        // if nums[j+1:i] is a valid subarray,
        // then count[i] - count[j] = k
        const int n = nums.size();
        // base case: nums[0:i] is valid
        // count[j] = count[i] - k = 0
        std::unordered_map<int, int> map;
        map[0] = 1;
        int result = 0;
        for (int i = 0, count = 0; i < n; ++i) {
            count += nums[i] % 2;
            const int target = count - k;
            if (target >= 0 && map.count(target)) {
                result += map[target];
            }
            map[count]++;
        }
        return result;
    }
};