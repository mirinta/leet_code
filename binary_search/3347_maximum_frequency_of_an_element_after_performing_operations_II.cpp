#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums and two integers k and numOperations.
 *
 * You must perform an operation numOperations times on nums, where in each operation you:
 *
 * - Select an index i that was not selected in any previous operations.
 *
 * - Add an integer in the range [-k, k] to nums[i].
 *
 * Return the maximum possible frequency of any element in nums after performing the operations.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 1 <= nums[i] <= 10^9
 * ! 0 <= k <= 10^9
 * ! 0 <= numOperations <= nums.length
 */

class Solution
{
public:
    int maxFrequency(std::vector<int>& nums, int k, int numOperations)
    {
        std::unordered_map<long long, long long> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        const int m = map.size();
        std::vector<long long> unique;
        unique.reserve(m);
        for (const auto& [val, count] : map) {
            unique.emplace_back(val);
        }
        std::sort(unique.begin(), unique.end());
        std::vector<long long> presum(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            presum[i] = presum[i - 1] + map[unique[i - 1]];
        }
        long long result = 0;
        for (int i = 0; i < m; ++i) {
            for (long long f = -1; f <= 1; ++f) {
                const auto val = f * k + nums[i];
                const auto lower =
                    std::lower_bound(unique.begin(), unique.end(), val - k) - unique.begin();
                const auto upper =
                    std::upper_bound(unique.begin(), unique.end(), val + k) - unique.begin();
                result = std::max(result, map[val] + std::min<long long>(
                                                         numOperations,
                                                         presum[upper] - presum[lower] - map[val]));
            }
        }
        return result;
    }
};
