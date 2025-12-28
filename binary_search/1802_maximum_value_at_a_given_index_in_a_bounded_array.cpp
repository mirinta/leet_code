#include <utility>

/**
 * You are given three positive integers: n, index, and maxSum. You want to construct an array nums
 * (0-indexed) that satisfies the following conditions:
 *
 * - nums.length == n.
 *
 * - nums[i] is a positive integer where 0 <= i < n.
 *
 * - abs(nums[i], nums[i + 1]) <= 1 where 0 <= i < n - 1.
 *
 * - The sum of all the elements of nums does not exceed maxSum.
 *
 * - nums[index] is maximized.
 *
 * Return nums[index] of the constructed array.
 *
 * Note that abs(x) equals x if x >= 0, and -x otherwise.
 *
 * ! 1 <= n <= maxSum <= 10^9
 * ! 0 <= index < n
 */

class Solution {
public:
    int maxValue(int n, int index, int maxSum)
    {
        int lo = 1;
        int hi = maxSum;
        while (lo < hi) {
            // infinite loop: const int mid = lo + (hi - lo) / 2;
            const int mid = hi - (hi - lo) / 2;
            if (isValid(mid, n, index, maxSum)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }
        return lo;
    }

private:
    bool isValid(long val, long n, long index, long maxSum)
    {
        //  |           val           |
        //  |     go up / \ go down   |
        //  |          /   \          |
        //  | 1 1 1 1 X     X 1 1 1 1 |
        //  0          index          n-1
        // where X >= 1
        // AP sequence with common difference 1: #items = (last - first) + 1, diff = 1
        const long leftAPItems = std::max(0L, std::min(val - 1, index));
        const long leftRemainingItems = std::max(0L, index - leftAPItems);
        const long leftSum = (val - 1 + val - leftAPItems) * leftAPItems / 2 + leftRemainingItems;

        const long rightAPItems = std::max(0L, std::min(val - 1, n - index - 1));
        const long rightRemainingItems = std::max(0L, n - index - 1 - rightAPItems);
        const long rightSum = (val - 1 + val - rightAPItems) * rightAPItems / 2 + rightRemainingItems;

        return leftSum + rightSum + val <= maxSum;
    }
};