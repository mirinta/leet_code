#include <stack>
#include <unordered_map>
#include <vector>

/**
 * You are given an array of positive integers nums.
 *
 * Return the number of subarrays of nums, where the first and the last elements of the subarray are
 * equal to the largest element in the subarray.
 *
 * ! 1 <= nums.length <= 105
 * ! 1 <= nums[i] <= 109
 */

class Solution {
public:
    long long numberOfSubarrays(std::vector<int>& nums)
    {
        // dp[i] = num of valid subarrays of nums[0:i] ending at nums[i]
        const int n = nums.size();
        const auto prevGreater = getPrevGreater(nums);
        std::unordered_map<int, int> lastSeen;
        std::vector<long long> dp(n);
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            const int j = prevGreater[i];
            if (lastSeen.count(nums[i]) && j < lastSeen[nums[i]]) {
                dp[i] = dp[lastSeen[nums[i]]] + 1;
            } else {
                dp[i] = 1;
            }
            lastSeen[nums[i]] = i;
            result += dp[i];
        }
        return result;
    }

private:
    std::vector<int> getPrevGreater(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] >= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }
};