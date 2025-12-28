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
    // prefix sum + hash table, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums, int goal)
    {
        // let presum[i] = sum of nums[0:i-1]
        // sum of nums[j:i] = presum[i+1] - presum[j]
        // given index i, we need to find the num of index j
        // such that presum[i+1] - presum[j] = goal
        // i.e., presum[j] = presum[i+1] - goal
        const int n = nums.size();
        std::vector<int> presum(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            presum[i] = presum[i - 1] + nums[i - 1];
        }
        std::unordered_map<int, int> map;
        map[0] = 1; // for the cases that presum[i+1] - goal = 0
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int target = presum[i + 1] - goal;
            if (map.find(target) != map.end()) {
                result += map[target];
            }
            map[presum[i + 1]]++;
        }
        return result;
    }

    // sliding window, TC = O(N), SC = O(1)
    // #NOTE# this approach only works for all nums[i] >= 0
    // because the sum doesn't grow monotonically with the window size
    int approach1(const std::vector<int>& nums, int goal)
    {
        return helper(nums, goal) - helper(nums, goal - 1);
    }

    // return num of subarrays such that sum of elements <= max
    int helper(const std::vector<int>& nums, int max)
    {
        const int n = nums.size();
        int sum = 0;
        int result = 0;
        for (int left = 0, right = 0; right < n; ++right) {
            sum += nums[right];
            while (left <= right && sum > max) {
                sum -= nums[left];
                left++;
            }
            result += right - left + 1; // num of valid subarrays ending at nums[right]
        }
        return result;
    }
};