#include <vector>

/**
 * You are given an array of positive integers nums.
 *
 * You have to check if it is possible to select two or more elements in the array such that the
 * bitwise OR of the selected elements has at least one trailing zero in its binary representation.
 *
 * For example, the binary representation of 5, which is "101", does not have any trailing zeros,
 * whereas the binary representation of 4, which is "100", has two trailing zeros.
 *
 * Return true if it is possible to select two or more elements whose bitwise OR has trailing zeros,
 * return false otherwise.
 *
 * ! 2 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 */

class Solution {
public:
    bool hasTrailingZeros(std::vector<int>& nums)
    {
        int count = 0;
        for (const auto& val : nums) {
            if ((val & 1) == 0) {
                count++;
            }
            if (count >= 2)
                return true;
        }
        return false;
    }
};