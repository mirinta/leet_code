#include <stack>
#include <vector>

/**
 * You are given a 0-indexed array nums of distinct integers.
 *
 * Let us define a 0-indexed array ans of the same length as nums in the following way:
 *
 * ans[i] is the maximum length of a subarray nums[l..r], such that the maximum element in that
 * subarray is equal to nums[i]. Return the array ans.
 *
 * Note that a subarray is a contiguous part of the array.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! All elements in nums are distinct.
 */

class Solution {
public:
    std::vector<int> maximumLengthOfRanges(std::vector<int>& nums)
    {
        const int n = nums.size();
        const auto prevGreater = getPrevGreater(nums);
        const auto nextGreater = getNextGreater(nums);
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            const int left = prevGreater[i];
            const int right = nextGreater[i];
            result[i] = right - left - 1;
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

    std::vector<int> getNextGreater(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] >= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};