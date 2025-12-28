#include <algorithm>
#include <vector>

/**
 * Given a sorted integer array nums and an integer n, add/patch elements to the array such that any
 * number in the range [1, n] inclusive can be formed by the sum of some elements in the array.
 *
 * Return the minimum number of patches required.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 10^4
 * ! nums is sorted in ascending order.
 * ! 1 <= n <= 2^31 - 1
 */

class Solution {
public:
    int minPatches(std::vector<int>& nums, int n)
    {
        // same as LC 2952
        // assume we can obtain [0:x] using nums[0:i-1]
        // after adding nums[i], we have two ranges:
        // [0:x] and [nums[i]:nums[i]+x]
        // if nums[i] = x+1 or nums[i] <= x, then we can obtain [0:nums[i]+x]
        //
        // otherwise, we need to add a new integer x+1
        // then the range becomes [0:2x+1]
        long long x = 0;
        int i = 0;
        int result = 0;
        while (x < n) {
            if (i < nums.size() && (nums[i] == x + 1 || nums[i] <= x)) {
                x += nums[i];
                i++;
            } else {
                x = 2 * x + 1;
                result++;
            }
        }
        return result;
    }
};