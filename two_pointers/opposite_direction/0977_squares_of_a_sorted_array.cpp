#include <vector>

/**
 * Given an integer array nums sorted in non-decreasing order, return an array of the squares of
 * each number sorted in non-decreasing order.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -10^4 <= nums[i] <= 10^4
 * ! nums is sorted in non-decreasing order.
 */

class Solution {
public:
    std::vector<int> sortedSquares(const std::vector<int>& nums)
    {
        const int n = nums.size();
        std::vector<int> result(n);
        for (int i = n - 1, left = 0, right = n - 1; i >= 0; --i) {
            if (std::abs(nums[left]) > std::abs(nums[right])) {
                result[i] = nums[left] * nums[left];
                left++;
            } else {
                result[i] = nums[right] * nums[right];
                right--;
            }
        }
        return result;
    }
};