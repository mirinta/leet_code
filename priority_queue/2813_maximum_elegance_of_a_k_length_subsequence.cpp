#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

/**
 * You are given a 0-indexed 2D integer array items of length n and an integer k.
 *
 * items[i] = [profiti, categoryi], where profiti and categoryi denote the profit and category of
 * the ith item respectively.
 *
 * Let's define the elegance of a subsequence of items as total_profit + distinct_categories2, where
 * total_profit is the sum of all profits in the subsequence, and distinct_categories is the number
 * of distinct categories from all the categories in the selected subsequence.
 *
 * Your task is to find the maximum elegance from all subsequences of size k in items.
 *
 * Return an integer denoting the maximum elegance of a subsequence of items with size exactly k.
 *
 * Note: A subsequence of an array is a new array generated from the original array by deleting some
 * elements (possibly none) without changing the remaining elements' relative order.
 *
 * ! 1 <= items.length == n <= 10^5
 * ! items[i].length == 2
 * ! items[i][0] == profiti
 * ! items[i][1] == categoryi
 * ! 1 <= profiti <= 10^9
 * ! 1 <= categoryi <= n
 * ! 1 <= k <= n
 */

class Solution {
public:
    long long findMaximumElegance(std::vector<std::vector<int>>& items, int k)
    {
        std::sort(items.begin(), items.end(), [](const auto& v1, const auto& v2) { return v1[0] > v2[0]; });
        using Pair = std::pair<long long, int>; // <profit, category>
        auto compare = [](const auto& p1, const auto& p2) { return p1.first > p2.first; };
        std::priority_queue<Pair, std::vector<Pair>, decltype(compare)> pq(compare);
        std::unordered_map<int, int> map;
        long long totalProfit = 0;
        for (int i = 0; i < k; ++i) {
            totalProfit += items[i][0];
            map[items[i][1]]++;
            pq.emplace(items[i][0], items[i][1]);
        }
        long long result = totalProfit + map.size() * map.size();
        for (int i = k; i < items.size(); ++i) {
            if (map.count(items[i][1]))
                continue;

            while (!pq.empty()) {
                const auto [profit, category] = pq.top();
                pq.pop();
                if (map[category] > 1) {
                    map[category]--;
                    map[items[i][1]]++;
                    totalProfit -= profit;
                    totalProfit += items[i][0];
                    result = std::max<long long>(result, totalProfit + map.size() * map.size());
                    break;
                }
            }
        }
        return result;
    }
};