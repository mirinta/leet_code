#include <stack>
#include <unordered_map>
#include <vector>

/**
 * The next greater element of some element x in an array is the first greater element that is to
 * the right of x in the same array.
 *
 * You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1 is a subset of
 * nums2.
 *
 * For each 0 <= i < nums1.length, find the index j such that nums1[i] == nums2[j] and determine the
 * next greater element of nums2[j] in nums2. If there is no next greater element, then the answer
 * for this query is -1.
 *
 * Return an array ans of length nums1.length such that ans[i] is the next greater element as
 * described above.
 *
 * ! 1 <= nums1.length <= nums2.length <= 1000
 * ! 0 <= nums1[i], nums2[i] <= 10^4
 * ! All integers in nums1 and nums2 are unique.
 * ! All the integers of nums1 also appear in nums2.
 */

class Solution {
public:
    std::vector<int> nextGreaterElement(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        const int n = nums2.size();
        std::unordered_map<int, int> map;
        for (int i = 0; i < n; ++i) {
            map[nums2[i]] = i;
        }
        const auto nextGreater = getNextGreater(nums2);
        const int m = nums1.size();
        std::vector<int> result(m);
        for (int i = 0; i < m; ++i) {
            result[i] = nextGreater[map[nums1[i]]];
        }
        return result;
    }

private:
    std::vector<int> getNextGreater(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::stack<int> stack;
        std::vector<int> result(n);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] >= nums[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : nums[stack.top()];
            stack.push(i);
        }
        return result;
    }
};