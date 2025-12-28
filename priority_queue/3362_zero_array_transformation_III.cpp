#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given an integer array nums of length n and a 2D array queries where queries[i] = [li,
 * ri].
 *
 * Each queries[i] represents the following action on nums:
 *
 * - Decrement the value at each index in the range [li, ri] in nums by at most 1.
 *
 * - The amount by which the value is decremented can be chosen independently for each index.
 *
 * A Zero Array is an array with all its elements equal to 0.
 *
 * Return the maximum number of elements that can be removed from queries, such that nums can still
 * be converted to a zero array using the remaining queries. If it is not possible to convert nums
 * to a zero array, return -1.
 *
 * ! 1 <= nums.length <= 10^5
 * ! 0 <= nums[i] <= 10^5
 * ! 1 <= queries.length <= 10^5
 * ! queries[i].length == 2
 * ! 0 <= li <= ri < nums.length
 */

class Solution {
public:
    int maxRemoval(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        std::sort(queries.begin(), queries.end(), [](const auto& q1, const auto& q2) { return q1[0] < q2[0]; });
        std::priority_queue<int> pq;
        std::vector<int> diff(nums.size(), 0);
        for (int i = 0, j = 0, decrement = 0; i < nums.size(); ++i) {
            decrement += diff[i];
            while (j < queries.size() && queries[j][0] == i) {
                pq.emplace(queries[j][1]);
                j++;
            }
            while (nums[i] > decrement && !pq.empty() && pq.top() >= i) {
                decrement++;
                const auto end = pq.top();
                pq.pop();
                if (end + 1 < nums.size()) {
                    diff[end + 1]--;
                }
            }
            if (nums[i] > decrement)
                return -1;
        }
        return pq.size();
    }
};
