#include <vector>

/**
 * You are given an integer array nums, an integer array queries, and an integer x.
 *
 * For each queries[i], you need to find the index of the queries[i]th occurrence of x in the nums
 * array. If there are fewer than queries[i] occurrences of x, the answer should be -1 for that
 * query.
 *
 * Return an integer array answer containing the answers to all queries.
 *
 * ! 1 <= nums.length, queries.length <= 10^5
 * ! 1 <= queries[i] <= 10^5
 * ! 1 <= nums[i], x <= 10^4
 */

class Solution {
public:
    std::vector<int> occurrencesOfElement(std::vector<int>& nums, std::vector<int>& queries, int x)
    {
        const int n = nums.size();
        std::vector<int> indices;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == x) {
                indices.push_back(i);
            }
        }
        std::vector<int> result;
        result.reserve(queries.size());
        for (const auto& i : queries) {
            if (i - 1 < 0 || i - 1 >= indices.size()) {
                result.push_back(-1);
            } else {
                result.push_back(indices[i - 1]);
            }
        }
        return result;
    }
};