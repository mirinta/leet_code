#include <stack>
#include <vector>

/**
 * You are given an integer array nums. The range of a subarray of nums is the difference between
 * the largest and smallest element in the subarray.
 *
 * Return the sum of all subarray ranges of nums.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * ! 1 <= nums.length <= 1000
 * ! -10^9 <= nums[i] <= 10^9
 *
 * ! Could you find a solution with O(n) time complexity?
 */

class Solution {
public:
    long long subArrayRanges(std::vector<int>& nums)
    {
        const int n = nums.size();
        const auto prevSmaller = getPrevSmaller(nums);
        const auto prevGreater = getPrevGreater(nums);
        const auto nextSmallerOrEqual = getNextSmallerOrEqual(nums);
        const auto nextGreaterOrEqual = getNextGreaterOrEqual(nums);
        long long result = 0;
        for (long long i = 0; i < n; ++i) {
            const long long a = (i - prevSmaller[i]) * (nextSmallerOrEqual[i] - i);
            const long long b = (i - prevGreater[i]) * (nextGreaterOrEqual[i] - i);
            result += (b - a) * nums[i];
        }
        return result;
    }

private:
    std::vector<long long> getPrevSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<long long> stack;
        std::vector<long long> result(n);
        for (long long i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<long long> getPrevGreater(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<long long> stack;
        std::vector<long long> result(n);
        for (long long i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] >= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<long long> getNextSmallerOrEqual(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<long long> stack;
        std::vector<long long> result(n);
        for (long long i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] < nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }

    std::vector<long long> getNextGreaterOrEqual(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<long long> stack;
        std::vector<long long> result(n);
        for (long long i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] > nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};