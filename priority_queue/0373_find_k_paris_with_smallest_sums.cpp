#include <queue>
#include <vector>

/**
 * You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
 *
 * Define a pair (u, v) which consists of one element from the first array and one element from the
 * second array.
 *
 * Return the k pairs (u1, v1), (u2, v2), ..., (uk, vk) with the smallest sums.
 *
 * ! 1 <= nums1.length, nums2.length <= 10^5
 * ! -10^9 <= nums1[i], nums2[i] <= 10^9
 * ! nums1 and nums2 both are sorted in ascending order.
 * ! 1 <= k <= 10^4
 */

class Solution {
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int>& nums1, std::vector<int>& nums2, int k)
    {
        const int m = nums1.size();
        const int n = nums2.size();
        using Pair = std::pair<int, int>; // <index of nums1, index of nums2>
        auto comparator = [&nums1, &nums2](const auto& p1, const auto& p2) {
            return nums1[p1.first] + nums2[p1.second] > nums1[p2.first] + nums2[p2.second];
        };
        std::priority_queue<Pair, std::vector<Pair>, decltype(comparator)> pq(comparator);
        for (int i = 0; i < m; ++i) {
            pq.emplace(i, 0);
        }
        std::vector<std::vector<int>> result;
        while (!pq.empty() && k > 0) {
            k--;
            const auto [i, j] = pq.top();
            pq.pop();
            result.push_back({nums1[i], nums2[j]});
            if (j + 1 < n) {
                pq.emplace(i, j + 1);
            }
        }
        return result;
    }
};
