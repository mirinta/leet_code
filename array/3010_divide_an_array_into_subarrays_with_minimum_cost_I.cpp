#include <vector>

/**
 * You are given an array of integers nums of length n.
 *
 * The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1
 * while the cost of [3,4,1] is 3.
 *
 * You need to divide nums into 3 disjoint contiguous subarrays.
 *
 * Return the minimum possible sum of the cost of these subarrays.
 *
 * ! 3 <= n <= 50
 * ! 1 <= nums[i] <= 50
 */

class Solution {
public:
    int minimumCost(std::vector<int>& nums)
    {
        // part1: [0:i]
        // part2: [i+1:j]
        // part3: [j+1:n-1]
        // cost = nums[0] + nums[i+1] + nums[j+1]
        // just find the smallest and the second smallest element of nums[1:n)
        int min = INT_MAX;
        int secondMin = INT_MAX;
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] < min) {
                std::swap(min, secondMin);
                min = nums[i];
            } else if (nums[i] < secondMin) {
                secondMin = nums[i];
            }
        }
        return nums[0] + min + secondMin;
    }
};