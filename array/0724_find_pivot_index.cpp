#include <numeric>
#include <vector>

/**
 * Given an array of integers nums, calculate the pivot index of this array.
 *
 * The pivot index is the index where the sum of all the numbers strictly to the left of the index
 * is equal to the sum of all the numbers strictly to the index's right.
 *
 * If the index is on the left edge of the array, then the left sum is 0 because there are no
 * elements to the left. This also applies to the right edge of the array.
 *
 * Return the leftmost pivot index. If no such index exists, return -1.
 *
 * ! 1 <= nums.length <= 10^4
 * ! -1000 <= nums[i] <= 1000
 *
 * ! This question is the same as LC.1991.
 */

class Solution {
public:
    int pivotIndex(std::vector<int>& nums)
    {
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        for (int i = 0, sum = 0; i < nums.size(); ++i) {
            if (sum == total - sum - nums[i])
                return i;

            sum += nums[i];
        }
        return -1;
    }
};