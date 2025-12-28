#include <cmath>
#include <vector>

/**
 * Given an array "nums" of "n" integers where nums[i] is in the range [1, n], return an array of
 * all the integers in the range [1, n] that do not appear in nums.
 *
 * ! Could you do it without extra space and in O(n) runtime?
 * ! You may assume the returned list does not count as extra space.
 */

class Solution {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        for (size_t i = 0; i < nums.size(); ++i) {
            const auto index = std::abs(nums[i]) - 1;
            if (nums[index] > 0) {
                nums[index] *= -1;
            }
        }
        std::vector<int> result;
        for (size_t i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }
        return result;
    }
};