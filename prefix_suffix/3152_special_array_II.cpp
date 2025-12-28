#include <vector>

/**
 * An array is considered special if every pair of its adjacent elements contains two numbers with
 * different parity.
 *
 * You are given an array of integer nums and a 2D integer matrix queries, where for queries[i] =
 * [fromi, toi] your task is to check that subarray nums[fromi..toi] is special or not.
 *
 * Return an array of booleans answer such that answer[i] is true if nums[fromi..toi] is special.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length == 2
 * ! 0 <= queries[i][0] <= queries[i][1] <= nums.length - 1
 */

class Solution {
public:
    std::vector<bool> isArraySpecial(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        const int n = nums.size();
        std::vector<int> v;
        v.reserve(n - 1);
        for (int i = 0; i + 1 < n; ++i) {
            v.push_back(nums[i] % 2 == nums[i + 1] % 2);
        }
        std::vector<int> presum(v.size() + 1, 0);
        for (int i = 1; i < presum.size(); ++i) {
            presum[i] = presum[i - 1] + v[i - 1];
        }
        std::vector<bool> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            const auto& from = q[0];
            const auto& to = q[1];
            result.push_back(presum[to] - presum[from] == 0);
        }
        return result;
    }
};