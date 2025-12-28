#include <queue>
#include <vector>

/**
 * You are given an integer array nums, an integer k, and an integer multiplier.
 *
 * You need to perform k operations on nums. In each operation:
 *
 * - Find the minimum value x in nums. If there are multiple occurrences of the minimum value,
 * select the one that appears first.
 *
 * - Replace the selected minimum value x with x * multiplier.
 *
 * Return an integer array denoting the final state of nums after performing all k operations.
 *
 * ! 1 <= nums.length <= 100
 * ! 1 <= nums[i] <= 100
 * ! 1 <= k <= 10
 * ! 1 <= multiplier <= 5
 */

class Solution {
public:
    std::vector<int> getFinalState(std::vector<int>& nums, int k, int multiplier)
    {
        using Pair = std::pair<int, int>; // <value, index>
        struct Compare {
            bool operator()(const Pair& p1, const Pair& p2) const
            {
                if (p1.first == p2.first)
                    return p1.second > p2.second;

                return p1.first > p2.first;
            }
        };
        const int n = nums.size();
        std::priority_queue<Pair, std::vector<Pair>, Compare> pq;
        for (int i = 0; i < n; ++i) {
            pq.emplace(nums[i], i);
        }
        std::vector<int> result(nums);
        for (int i = 0; i < k; ++i) {
            const auto [val, idx] = pq.top();
            pq.pop();
            result[idx] = val * multiplier;
            pq.emplace(result[idx], idx);
        }
        return result;
    }
};