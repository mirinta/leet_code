#include <climits>
#include <unordered_map>
#include <vector>

/**
 * You are given an integer array nums.
 *
 * A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].
 *
 * The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.
 *
 * Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.
 *
 * ! 1 <= n == nums.length <= 10^5
 * ! 1 <= nums[i] <= n
 */

class Solution {
public:
    int minimumDistance(std::vector<int>& nums)
    {
        const int n = nums.size();
        std::unordered_map<int, std::vector<int>> map;
        for (int i = 0; i < n; ++i) {
            map[nums[i]].push_back(i);
        }
        int result = INT_MAX;
        for (const auto& [_, indices] : map) {
            if (indices.size() < 3)
                continue;

            const int m = indices.size();
            for (int i = 2; i < m; ++i) {
                result = std::min(result, 2 * (indices[i] - indices[i - 2]));
            }
        }
        return result == INT_MAX ? -1 : result;
    }
};
