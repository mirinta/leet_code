#include <vector>

/**
 * You are given an integer array nums of length n and a 2D array queries where queries[i] = [li,
 * ri, vali].
 *
 * Each queries[i] represents the following action on nums:
 *
 * - Decrement the value at each index in the range [li, ri] in nums by at most vali.
 *
 * - The amount by which each value is decremented can be chosen independently for each index.
 *
 * A Zero Array is an array with all its elements equal to 0.
 *
 * Return the minimum possible non-negative value of k, such that after processing the first k
 * queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 5 * 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length == 3
 * ! 0 <= li <= ri < nums.length
 * ! 1 <= vali <= 5
 */

class Solution {
public:
    int minZeroArray(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        int lo = 0;
        int hi = queries.size();
        while (lo <= hi) {
            const int mid = lo + (hi - lo) / 2;
            if (isValid(mid, nums, queries)) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return lo > queries.size() ? -1 : lo;
    }

private:
    bool isValid(int k, const std::vector<int>& nums, const std::vector<std::vector<int>>& queries)
    {
        const int n = nums.size();
        std::vector<int> diff(n, 0);
        for (int i = 0; i < k; ++i) {
            diff[queries[i][0]] += queries[i][2];
            if (queries[i][1] + 1 < n) {
                diff[queries[i][1] + 1] -= queries[i][2];
            }
        }
        for (int i = 0, decrement = 0; i < n; ++i) {
            decrement += diff[i];
            if (nums[i] - decrement > 0)
                return false;
        }
        return true;
    }
};
