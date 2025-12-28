#include <cmath>
#include <vector>

/**
 * You are given a positive integer k. Initially, you have an array nums = [1].
 *
 * You can perform any of the following operations on the array any number of times (possibly zero):
 *
 * - Choose any element in the array and increase its value by 1.
 *
 * - Duplicate any element in the array and add it to the end of the array.
 *
 * Return the minimum number of operations required to make the sum of elements of the final array
 * greater than or equal to k.
 *
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    int minOperations(int k)
    {
        int result = INT_MAX;
        for (int i = 1; i <= k; ++i) {
            const int val = std::ceil(k * 1.0 / i);
            const int count = (i - 1) + (val - 1);
            result = std::min(result, count);
        }
        return result;
    }
};