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
 * ! 1 <= nums[i] <= 10^5
 * ! 0 <= k <= 10^5
 * ! 0 <= numOperations <= nums.length
 */

class Solution {
public:
    int maxFrequency(std::vector<int>& nums, int k, int numOperations)
    {
        std::unordered_map<int, int> map;
        for (const auto& val : nums) {
            map[val]++;
        }
        const int m = map.size();
        std::vector<int> unique;
        unique.reserve(m);
        for (const auto& [val, count] : map) {
            unique.emplace_back(val);
        }
        std::sort(unique.begin(), unique.end());
        std::vector<int> presum(m + 1, 0);
        for (int i = 1; i <= m; ++i) {
            presum[i] = presum[i - 1] + map[unique[i - 1]];
        }
        int result = 0;
        for (int val = unique.front(); val <= unique.back(); ++val) {
            const int lower = std::lower_bound(unique.begin(), unique.end(), val - k) - unique.begin();
            const int upper = std::upper_bound(unique.begin(), unique.end(), val + k) - unique.begin();
            result = std::max(result, map[val] + std::min(numOperations, presum[upper] - presum[lower] - map[val]));
        }
        return result;
    }
};
