#include <vector>

/**
 * Given the array queries of positive integers between 1 and m, you have to process all queries[i]
 * (from i=0 to i=queries.length-1) according to the following rules:
 *
 * - In the beginning, you have the permutation P=[1,2,3,...,m].
 *
 * - For the current i, find the position of queries[i] in the permutation P (indexing from 0) and
 * then move this at the beginning of the permutation P. Notice that the position of queries[i] in P
 * is the result for queries[i].
 *
 * Return an array containing the result for the given queries.
 *
 * ! 1 <= m <= 10^3
 * ! 1 <= queries.length <= m
 * ! 1 <= queries[i] <= m
 */

class Solution {
public:
    std::vector<int> processQueries(std::vector<int>& queries, int m)
    {
        const int n = queries.size();
        std::vector<int> nums(m);
        for (int j = 0; j < m; ++j) {
            nums[j] = j + 1;
        }
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            const auto& target = queries[i];
            for (int j = 0; j < m; ++j) {
                if (nums[j] == target) {
                    result[i] = j;
                    break;
                }
            }
            nums.erase(nums.begin() + result[i]);
            nums.insert(nums.begin(), target);
        }
        return result;
    }
};