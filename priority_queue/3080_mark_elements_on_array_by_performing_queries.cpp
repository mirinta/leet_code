#include <numeric>
#include <queue>
#include <vector>

/**
 * You are given a 0-indexed array nums of size n consisting of positive integers.
 *
 * You are also given a 2D array queries of size m where queries[i] = [indexi, ki].
 *
 * Initially all elements of the array are unmarked.
 *
 * You need to apply m queries on the array in order, where on the ith query you do the following:
 *
 * - Mark the element at index indexi if it is not already marked.
 *
 * - Then mark ki unmarked elements in the array with the smallest values. If multiple such elements
 * exist, mark the ones with the smallest indices. And if less than ki unmarked elements exist, then
 * mark all of them.
 *
 * Return an array answer of size m where answer[i] is the sum of unmarked elements in the array
 * after the ith query.
 *
 * ! n == nums.length
 * ! m == queries.length
 * ! 1 <= m <= n <= 10^5
 * ! 1 <= nums[i] <= 10^5
 * ! queries[i].length == 2
 * ! 0 <= indexi, ki <= n - 1
 */

class Solution {
public:
    std::vector<long long> unmarkedSumArray(std::vector<int>& nums, std::vector<std::vector<int>>& queries)
    {
        const int n = nums.size();
        using Pair = std::pair<int, int>;
        std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
        for (int i = 0; i < n; ++i) {
            pq.emplace(nums[i], i);
        }
        std::vector<bool> marked(n, false);
        long long total = std::accumulate(nums.begin(), nums.end(), 0LL);
        std::vector<long long> result(queries.size(), 0);
        for (int i = 0; i < queries.size(); ++i) {
            const int index = queries[i][0];
            if (!marked[index]) {
                marked[index] = true;
                total -= nums[index];
            }
            int k = queries[i][1];
            while (!pq.empty() && k) {
                const auto [val, j] = pq.top();
                pq.pop();
                if (!marked[j]) {
                    marked[j] = true;
                    total -= nums[j];
                    k--;
                }
            }
            result[i] = total;
        }
        return result;
    }
};