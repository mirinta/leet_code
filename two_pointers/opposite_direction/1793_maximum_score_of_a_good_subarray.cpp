#include <stack>
#include <vector>

/**
 * You are given an array of integers nums (0-indexed) and an integer k.
 *
 * The score of a subarray (i, j) is defined as min(nums[i], nums[i+1], ..., nums[j]) * (j - i + 1).
 * A good subarray is a subarray where i <= k <= j.
 *
 * Return the maximum possible score of a good subarray.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 2 * 10^4
 * ! 0 <= k < nums.length
 */

class Solution {
public:
    int maximumScore(std::vector<int>& nums, int k)
    {
        return approach2(nums, k);
    }

private:
    // two pointers, TC = O(N), SC = O(1)
    int approach2(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        int left = k;
        int right = k;
        int min = nums[k];
        int result = nums[k];
        while (left >= 0 || right < n) {
            while (left >= 0 && nums[left] >= min) {
                left--;
            }
            while (right < n && nums[right] >= min) {
                right++;
            }
            result = std::max(result, min * (right - left - 1));
            const int leftVal = left < 0 ? INT_MIN : nums[left];
            const int rightVal = right >= n ? INT_MIN : nums[right];
            min = std::max(leftVal, rightVal);
        }
        return result;
    }

    // monotonic stack, TC = O(N), SC = O(N)
    int approach1(const std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        const auto prevSmaller = getPrevSmaller(nums);
        const auto nextSmaller = getNextSmaller(nums);
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int left = prevSmaller[i] + 1;
            const int right = nextSmaller[i] - 1;
            if (k >= left && k <= right) {
                result = std::max(result, nums[i] * (right - left + 1));
            }
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

    std::vector<int> getNextSmaller(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? n : stack.top();
            stack.push(i);
        }
        return result;
    }
};