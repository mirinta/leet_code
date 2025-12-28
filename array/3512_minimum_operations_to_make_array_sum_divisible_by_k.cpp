#include <numeric>
#include <vector>

/**
 * You are given an integer array nums and an integer k. You can perform the following operation any
 * number of times:
 *
 * - Select an index i and replace nums[i] with nums[i] - 1.
 *
 * Return the minimum number of operations required to make the sum of the array divisible by k.
 *
 * ! 1 <= nums.length <= 1000
 * ! 1 <= nums[i] <= 1000
 * ! 1 <= k <= 100
 */

class Solution {
public:
    int minOperations(std::vector<int>& nums, int k)
    {
        const int sum = std::accumulate(nums.begin(), nums.end(), 0);
        return sum % k;
    }
};