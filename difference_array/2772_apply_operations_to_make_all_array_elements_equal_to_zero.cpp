#include <vector>

/**
 * You are given a 0-indexed integer array nums and a positive integer k.
 *
 * You can apply the following operation on the array any number of times:
 *
 * - Choose any subarray of size k from the array and decrease all its elements by 1.
 *
 * Return true if you can make all the array elements equal to 0, or false otherwise.
 *
 * A subarray is a contiguous non-empty part of an array.
 *
 * ! 1 <= k <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^6
 */

class Solution {
public:
    bool checkArray(std::vector<int>& nums, int k)
    {
        // decrements[i] = k means nums[i] is decreased by k
        // diff[i] = decrements[i] - decrements[i-1], diff[0] = decrements[0]
        const int n = nums.size();
        std::vector<int> diff(n, 0);
        // nums[0] must be changed to 0, so we need to decrease nums[0],...,nums[k-1] by nums[0]
        diff[0] = nums[0];
        if (k < n) {
            diff[k] = -nums[0];
        }
        for (int i = 1; i < n; ++i) {
            // restore decrements[i] and check nums[i] - decrements[i]
            // case 1: nums[i] - decrements[i] = 0, we don't need extra decrements
            // case 2: nums[i] - decrements[i] < 0, nums[i] can not be changed to 0
            // case 3: nums[i] - decrements[i] > 0, we need extra decrements on nums[i]
            // - we have to decrease k elements in one operation
            // - it means nums[i],...,nums[i+k-1] must be decreased at the same time
            // - thus, we need to check i+k-1 < n
            diff[i] += diff[i - 1];
            const int decrements = diff[i];
            if (decrements == nums[i])
                continue;

            if (decrements > nums[i] || i + k - 1 >= n)
                return false;

            const int newDecrements = nums[i] - decrements;
            diff[i] += newDecrements;
            if (i + k < n) {
                diff[i + k] -= newDecrements;
            }
        }
        return true;
    }
};