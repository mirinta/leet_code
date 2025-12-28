#include <vector>

/**
 * Given an integer array "nums", handle multiple queries of the following type:
 *
 * Calculate the sum of the elements of "nums" between indices "left" and "right" inclusive where
 * left <= right.
 *
 * Implement the "NumArray" class:
 *
 * - "NumArray(int[] nums)" initializes the object with the integer array "nums".
 *
 * - "int sumRange(int left, int right)" returns the sum of the elements of "nums" between indices
 * "left" and "right" inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 *
 * ! At most 10^4 calls will be made to "sumRange".
 */

class NumArray {
    // [0, sumRange[0,0], sumRange[0,1], ..., sumRange[0, N-1]]
    const std::vector<int> _preSums;

    static std::vector<int> createPreSums(const std::vector<int>& nums)
    {
        std::vector<int> result(nums.size() + 1, 0);
        for (size_t i = 0; i < nums.size(); ++i) {
            result[i + 1] = result[i] + nums[i];
        }
        return result;
    }

public:
    NumArray(std::vector<int>& nums) : _preSums(createPreSums(nums)) {}

    int sumRange(int left, int right)
    {
        return _preSums[right + 1] - _preSums[left];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */