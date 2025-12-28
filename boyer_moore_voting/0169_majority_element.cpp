#include <vector>

/**
 * Given an array nums of size n, return the majority element.
 *
 * The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the
 * majority element always exists in the array.
 *
 * ! n == nums.length
 * ! 1 <= n <= 5 * 10^4
 * ! -10^9 <= nums[i] <= 10^9
 */

class Solution {
public:
    int majorityElement(std::vector<int>& nums)
    {
        // boyer-moore voting, TC = O(N), SC = O(1)
        int vote = 0;
        int result = INT_MIN;
        for (const auto& val : nums) {
            if (vote == 0) {
                result = val;
            }
            vote += result == val ? 1 : -1;
        }
        return result;
    }
};
