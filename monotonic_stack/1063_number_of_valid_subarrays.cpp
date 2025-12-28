#include <stack>
#include <vector>

/**
 * Given an integer array nums, return the number of non-empty subarrays with the leftmost element
 * of the subarray not larger than other elements in the subarray.
 *
 * A subarray is a contiguous part of an array.
 *
 * ! 1 <= nums.length <= 5 * 10^4
 * ! 0 <= nums[i] <= 10^5
 */

class Solution {
public:
    int validSubarrays(std::vector<int>& nums)
    {
        // i X X X X j
        // |<----->|
        // assume current number is nums[i], and
        // nums[j] is the next smaller element of nums[i]
        // then nums[i:j-1] are >= nums[i],
        // thus, there are j-i valid subarrays that start with nums[i]
        // if j doesn't exist, it means nums[i:n) are all >= nums[i]
        const int n = nums.size();
        std::vector<int> nextSmaller(n, -1); // nums[i]=j, nums[j] is the next smaller element of nums[i]
        std::stack<int> stack;
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] <= nums[stack.top()]) {
                stack.pop();
            }
            nextSmaller[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        int result = 0;
        for (int i = 0; i < n; ++i) {
            const int count = nextSmaller[i] < 0 ? n - i : nextSmaller[i] - i;
            result += count;
        }
        return result;
    }
};