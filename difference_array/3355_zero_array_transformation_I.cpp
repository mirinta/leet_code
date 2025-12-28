#include <vector>

/**
 * You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li,
 * ri].
 *
 * For each queries[i]:
 *
 * - Select a subset of indices within the range [li, ri] in nums.
 *
 * - Decrement the values at the selected indices by 1.
 *
 * A Zero Array is an array where all elements are equal to 0.
 *
 * Return true if it is possible to transform nums into a Zero Array after processing all the
 * queries sequentially, otherwise return false.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length == 2
 * ! 0 <= li <= ri < nums.length
 */

class Solution {
public:
    bool isZeroArray(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        const int n = nums.size();
        std::vector<int> diff(n, 0);
        for (const auto& q : queries) {
            diff[q[0]]++;
            if (q[1] + 1 < n) {
                diff[q[1] + 1]--;
            }
        }
        for (int i = 0, decrement = 0; i < n; ++i) {
            decrement += diff[i];
            if (nums[i] > decrement)
                return false;
        }
        return true;
    }
};