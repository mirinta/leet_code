#include <unordered_map>
#include <vector>

/**
 * Given a binary array nums and an integer goal, return the number of non-empty subarrays with a
 * sum goal.
 *
 * A subarray is a contiguous part of the array.
 *
 * ! 1 <= nums.length <= 3 * 10^4
 * ! nums[i] is either 0 or 1.
 * ! 0 <= goal <= nums.length
 */

class Solution {
public:
    int numSubarraysWithSum(std::vector<int>& nums, int goal)
    {
        return approach1(nums, goal);
    }

private:
    // prefix sum + hash map, TC = O(N), SC = O(N)
    int approach2(const std::vector<int>& nums, int goal)
    {
        // let presum[i] = sum of nums[0:i]
        // if nums[j+1:i] is valid,
        // sum of nums[j+1:i] = presum[i] - presum[j] = goal
        // thus, given presum[i], we need to know the occurrences of j such that
        // presum[j] = presum[i] - goal
        const int n = nums.size();
        // base case: nums[0:i] is valid
        // then presum[j] = presum[i] - goal = 0
        // thus, map[0] = 1
        std::unordered_map<int, int> map;
        map[0] = 1;
        int sum = 0;
        int result = 0;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            result += map[sum - goal];
            map[sum]++;
        }
        return result;
    }

    // sliding window, TC = O(N), SC = O(1)
    int approach1(const std::vector<int>& nums, int goal)
    {
        return solve(nums, goal) - solve(nums, goal - 1);
    }

    // num of subarrays with sum <= goal
    int solve(const std::vector<int>& nums, int goal)
    {
        const int n = nums.size();
        int sum = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while (left <= right && sum > goal) {
                sum -= nums[left];
                left++;
            }
            result += right - left + 1;
        }
        return result;
    }
};