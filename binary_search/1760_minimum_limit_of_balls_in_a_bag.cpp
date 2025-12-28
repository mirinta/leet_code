#include <algorithm>
#include <vector>

/**
 * You are given an integer array nums where the ith bag contains nums[i] balls. You are also given
 * an integer maxOperations.
 *
 * You can perform the following operation at most maxOperations times:
 *
 * - Take any bag of balls and divide it into two new bags with a positive number of balls.
 *
 * - For example, a bag of 5 balls can become two new bags of 1 and 4 balls, or two new bags of 2
 * and 3 balls.
 *
 * Your penalty is the maximum number of balls in a bag. You want to minimize your penalty after the
 * operations.
 *
 * Return the minimum possible penalty after performing the operations.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= maxOperations, nums[i] <= 10^9
 */

class Solution {
public:
    int minimumSize(std::vector<int>& nums, int maxOperations)
    {
        int lo = 1;
        int hi = *std::max_element(nums.begin(), nums.end());
        while (lo < hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums, maxOperations)) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        return lo;
    }

private:
    bool isValid(int max, const std::vector<int>& nums, int maxOperations)
    {
        int operations = 0;
        for (const auto& val : nums) {
            if (val <= max)
                continue;

            operations += val / max;
            if (val % max == 0) {
                operations--;
            }
            if (operations > maxOperations)
                return false;
        }
        return true;
    }
};
