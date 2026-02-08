#include <vector>

/**
 * You are given an integer array nums and an integer k.
 *
 * An array is considered balanced if the value of its maximum element is at most k times the minimum element.
 *
 * You may remove any number of elements from nums without making it empty.
 *
 * Return the minimum number of elements to remove so that the remaining array is balanced.
 *
 * Note: an array of size 1 is considered balanced as its maximum and minimum are equal, and the condition always holds
 * true.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    int minRemoval(std::vector<int>& nums, int k)
    {
        const int n = nums.size();
        std::sort(nums.begin(), nums.end());
        int result = INT_MAX;
        for (int left = 0, right = 0; right < n; ++right) {
            while (1LL * nums[left] * k < 1LL * nums[right]) {
                left++;
            }
            result = std::min(result, left + n - right - 1);
        }
        return result;
    }
};