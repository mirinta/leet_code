#include <cmath>
#include <vector>

/**
 * You are given a 0-indexed integer array nums. In one operation you can replace any element of the
 * array with any two elements that sum to it.
 *
 * - For example, consider nums = [5,6,7]. In one operation, we can replace nums[1] with 2 and 4 and
 * convert nums to [5,2,4,7].
 *
 * Return the minimum number of operations to make an array that is sorted in non-decreasing order.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 */

class Solution {
public:
    long long minimumReplacement(std::vector<int>& nums)
    {
        // 1. try to keep the last element unchanged as much as possible
        // 2. ... y x, x is the last element, y is the second to last element
        // If y <= x, no operations on x.
        // If y > x, say y = kx + b, there are k-1 operations
        // - If b == 0, there are k-1 operations.
        //   e.g. x = 4, y = 12, there are two operations:
        //   first, replace 12 with 4 and 8
        //   finally, replace 8 with 4 and 4
        //   it means y = 12 = 4 + 4 + 4
        // - If b != 0, try to #evenly divide# y into k+1 parts, there are k operations.
        //   Imagine we are trying to pour water with a volume of y into k+1 buckets,
        //   while maximize the water capacity of each bucket.
        //   e.g. x = 4, y = 13, there are three operations:
        //   first, replace 13 with 3 and 10
        //   then, replace 10 with 3 and 7
        //   finally, replace 7 with 3 and 4
        //   it means y = 13 = 3 + 3 + 3 + 4
        if (nums.size() < 2)
            return 0;

        long long result = 0;
        int x = nums.back();
        for (int i = nums.size() - 2; i >= 0; --i) {
            const int& y = nums[i];
            if (y <= x) {
                x = y; // update the last element
                continue;
            }
            const int numOfParts = std::ceil(y * 1.0 / x);
            result += numOfParts - 1;
            x = y / numOfParts; // update the last element
        }
        return result;
    }
};