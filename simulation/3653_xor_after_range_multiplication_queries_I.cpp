#include <vector>

/**
 * You are given an integer array nums of length n and a 2D integer array queries of size q, where queries[i] = [li, ri,
 * ki, vi].
 *
 * For each query, you must apply the following operations in order:
 *
 * - Set idx = li.
 *
 * - While idx <= ri:
 *
 *     - Update: nums[idx] = (nums[idx] * vi) % (109 + 7)
 *
 *     - Set idx += ki.
 *
 * Return the bitwise XOR of all elements in nums after processing all queries.
 *
 * ! 1 <= n == nums.length <= 10^3
 * ! 1 <= nums[i] <= 10^9
 * ! 1 <= q == queries.length <= 10^3
 * ! queries[i] = [li, ri, ki, vi]
 * ! 0 <= li <= ri < n
 * ! 1 <= ki <= n
 * ! 1 <= vi <= 10^5
 */

class Solution {
public:
    int xorAfterQueries(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        static constexpr int kMod = 1e9 + 7;
        for (const auto& q : queries) {
            for (int i = q[0]; i <= q[1]; i += q[2]) {
                nums[i] = (1LL * nums[i] * q[3]) % kMod;
            }
        }
        int result = 0;
        for (const auto& v : nums) {
            result ^= v;
        }
        return result;
    }
};
