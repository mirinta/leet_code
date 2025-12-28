#include <algorithm>
#include <cmath>
#include <vector>

/**
 * You are given a 0-indexed integer array nums containing positive integers.
 *
 * Your task is to minimize the length of nums by performing the following operations any number of
 * times (including zero):
 *
 * - Select two distinct indices i and j from nums, such that nums[i] > 0 and nums[j] > 0.
 *
 * - Insert the result of nums[i] % nums[j] at the end of nums.
 *
 * - Delete the elements at indices i and j from nums.
 *
 * Return an integer denoting the minimum length of nums after performing the operation any number
 * of times.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    int minimumArrayLength(std::vector<int>& nums)
    {
        // basic idea:
        // - in each operation, we want to pick A and B such that A % B != 0
        // - if A < B, then A % B = A, so we choose the min element of nums as A
        // - after each operation, the min is still in the array
        // discussion:
        // - if the frequency of min is 1, e.g. given nums = [min x1...xn]
        //   operation 1: pick min and x1, nums becomes [x2...xn min]
        //   operation 2: pick min and x2, nums becomes [x3...xn min]
        //   ...
        //   operation n-1: pick min and xn-1, nums becomes [xn min]
        //   operation n: pick min and xn, nums becomes [min]
        //   thus, result = 1
        // - if the frequency of min > 1, can we make a new element min' < min?
        //   if we can, based on the above discussion, we know that result = 1
        //   we know that A % B is in the range [0,B-1]
        //   thus, if there exists X such that X % min != 0, then min' = X % min
        // - if the frequency of min > 1 and we can't find X such that X % min != 0,
        //   then all elements are divisible by min, say nums = [min...min,2min,3min...qmin]
        //   assume the frequency of min = p
        //   operation 1: pick min and 2min, nums becomes [min...min,3min...qmin,min], frequency of
        //   min = p
        //   operation 2: pick min and 3min, nums becomes [min...min,4min...qmin,min],
        //   frequency of min = p
        //   ...
        //   finally, nums becomes [min...min], frequency of min = p
        //   if p is even, then result = p/2
        //   if p is odd, then result = (p-1)/2 + 1
        //   thus, result = std::ceil(p/2)
        const int min = *std::min_element(nums.begin(), nums.end());
        for (const auto& val : nums) {
            if (val % min != 0)
                return 1;
        }
        return std::ceil(std::count(nums.begin(), nums.end(), min) * 0.5);
    }
};