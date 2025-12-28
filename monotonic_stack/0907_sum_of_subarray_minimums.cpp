#include <stack>
#include <vector>

/**
 * Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous)
 * subarray of arr. Since the answer may be large, return the answer modulo 10^9 + 7.
 *
 * ! 1 <= arr.length <= 3 * 10^4
 * ! 1 <= arr[i] <= 3 * 10^4
 */

class Solution {
public:
    int sumSubarrayMins(std::vector<int>& arr)
    {
        return approach2(arr);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach2(const std::vector<int>& nums)
    {
        // count the num of subarrays that nums[i] is the min element
        const int n = nums.size();
        const auto prevSmaller = getPrevSmaller(nums);
        const auto nextSmallerOrEqual = getNextSmallerOrEqual(nums);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const long long count1 = i - prevSmaller[i];
            const long long count2 = nextSmallerOrEqual[i] - i;
            result = (result + count1 * count2 % kMod * nums[i] % kMod) % kMod;
        }
        return result;
    }

    std::vector<int> getNextSmallerOrEqual(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] < nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }

    int approach1(const std::vector<int>& nums)
    {
        // dp[i] = sum of min elements of all subarrays of nums[0:i] ending at nums[i]
        const auto prevSmaller = getPrevSmaller(nums);
        const int n = nums.size();
        std::vector<int> dp(n, 0);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int j = prevSmaller[i];
            if (j == -1) {
                // nums[i] is the min element of nums[0:i]
                dp[i] = static_cast<long long>(i + 1) * nums[i] % kMod;
            } else {
                // nums[i] is the min element of nums[j+1:i]
                dp[i] = (dp[j] + static_cast<long long>(i - j) * nums[i] % kMod) % kMod;
            }
            result = (result + dp[i]) % kMod;
        }
        return result;
    }

    std::vector<int> getPrevSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }
};