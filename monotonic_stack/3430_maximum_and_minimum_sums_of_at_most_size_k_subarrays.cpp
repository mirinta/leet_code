#include <stack>
#include <vector>

/**
 * You are given an integer array nums and a positive integer k. Return the sum of the maximum and
 * minimum elements of all subarrays with at most k elements.
 *
 * ! 1 <= nums.length <= 80000
 * ! 1 <= k <= nums.length
 * ! -10^6 <= nums[i] <= 10^6
 */

class Solution {
public:
    long long minMaxSubarraySum(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        const auto prevSmaller = getPrevSmaller(nums);
        const auto prevGreater = getPrevGreater(nums);
        const auto nextSmallerEq = getNextSmallerEq(nums);
        const auto nextGreaterEq = getNextGreaterEq(nums);
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            // nums[i] as the min element
            // j1 ... i-1 i i+1 ... j2
            // |<--Lx-->|   |<--Ly-->|
            // nums[j1:i-1] >= nums[i], nums[i+1:j2] > nums[i]
            int Lx = i - prevSmaller[i] - 1;
            int Ly = nextSmallerEq[i] - 1 - i;
            result += nums[i];
            result += 1LL * nums[i] * std::min(Lx, k - 1);
            result += 1LL * nums[i] * std::min(Ly, k - 1);
            if (Lx > 0 && Ly > 0 && k > 2) {
                long long count = 0;
                for (int left = 1; left <= std::min(Lx, k - 2); ++left) {
                    count += std::min(Ly, k - 1 - left);
                }
                result += count * nums[i];
            }
            // nums[i] as the max element
            // j1 ... i-1 i i+1 ... j2
            // |<--Lx-->|   |<--Ly-->|
            // nums[j1:i-1] <= nums[i], nums[i+1:j2] < nums[i]
            Lx = i - prevGreater[i] - 1;
            Ly = nextGreaterEq[i] - 1 - i;
            result += nums[i];
            result += 1LL * nums[i] * std::min(Lx, k - 1);
            result += 1LL * nums[i] * std::min(Ly, k - 1);
            if (Lx > 0 && Ly > 0 && k > 2) {
                long long count = 0;
                for (int left = 1; left <= std::min(Lx, k - 2); ++left) {
                    count += std::min(Ly, k - 1 - left);
                }
                result += count * nums[i];
            }
        }
        return result;
    }

private:
    std::vector<int> getPrevSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[stack.top()] >= nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> getPrevGreater(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[stack.top()] <= nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> getNextSmallerEq(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[stack.top()] > nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<int> getNextGreaterEq(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[stack.top()] < nums[i]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};