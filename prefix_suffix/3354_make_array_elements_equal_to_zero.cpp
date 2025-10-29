#include <numeric>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * Start by selecting a starting position curr such that nums[curr] == 0, and choose a movement
 * direction of either left or right.
 *
 * After that, you repeat the following process:
 *
 * - If curr is out of the range [0, n - 1], this process ends.
 *
 * - If nums[curr] == 0, move in the current direction by incrementing curr if you are moving right,
 * or decrementing curr if you are moving left.
 *
 * - Else if nums[curr] > 0:
 *
 *     - Decrement nums[curr] by 1.
 *
 *     - Reverse your movement direction (left becomes right and vice versa).
 *
 *     - Take a step in your new direction.
 *
 * A selection of the initial position curr and movement direction is considered valid if every
 * element in nums becomes 0 by the end of the process.
 *
 * Return the number of possible valid selections.
 *
 * ! 1 <= nums.length <= 100
 * ! 0 <= nums[i] <= 100
 * ! There is at least one element i where nums[i] == 0.
 */

class Solution
{
public:
    int countValidSelections(std::vector<int>& nums)
    {
        const int n = nums.size();
        const int total = std::accumulate(nums.begin(), nums.end(), 0);
        int result = 0;
        for (int i = 0, left = 0; i < n; ++i) {
            left += nums[i];
            if (nums[i] != 0)
                continue;

            const int right = total - left;
            result += left == right || left - right == 1;
            result += left == right || right - left == 1;
        }
        return result;
    }
};