#include <algorithm>
#include <queue>
#include <vector>

/**
 * You are given a 0-indexed m * n integer matrix values, representing the values of m * n different
 * items in m different shops. Each shop has n items where the jth item in the ith shop has a value
 * of values[i][j]. Additionally, the items in the ith shop are sorted in non-increasing order of
 * value. That is, values[i][j] >= values[i][j + 1] for all 0 <= j < n - 1.
 *
 * On each day, you would like to buy a single item from one of the shops. Specifically, On the dth
 * day you can:
 *
 * - Pick any shop i.
 *
 * - Buy the rightmost available item j for the price of values[i][j] * d. That is, find the
 * greatest index j such that item j was never bought before, and buy it for the price of
 * values[i][j] * d. Note that all items are pairwise different. For example, if you have bought
 * item 0 from shop 1, you can still buy item 0 from any other shop.
 *
 * Return the maximum amount of money that can be spent on buying all m * n products.
 *
 * ! 1 <= m == values.length <= 10
 * ! 1 <= n == values[i].length <= 10^4
 * ! 1 <= values[i][j] <= 10^6
 * ! values[i] are sorted in non-increasing order.
 */

class Solution {
public:
    long long maxSpending(std::vector<std::vector<int>>& values)
    {
        return approach2(values);
    }

private:
    long long approach2(std::vector<std::vector<int>>& values)
    {
        const int m = values.size();
        const int n = values[0].size();
        std::vector<long long> prices;
        prices.reserve(m * n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                prices.push_back(values[i][j]);
            }
        }
        std::sort(prices.begin(), prices.end());
        long long result = 0;
        for (int day = 1; day <= prices.size(); ++day) {
            result += prices[day - 1] * day;
        }
        return result;
    }

    long long approach1(std::vector<std::vector<int>>& values)
    {
        const int m = values.size();
        const int n = values[0].size();
        using Tuple = std::tuple<int, int, long long>; // <i, j, price>
        auto comparator = [](const auto& t1, const auto& t2) { return std::get<2>(t1) > std::get<2>(t2); };
        std::priority_queue<Tuple, std::vector<Tuple>, decltype(comparator)> pq(comparator); // min heap
        for (int i = 0; i < m; ++i) {
            pq.emplace(i, n - 1, values[i].back());
        }
        long long result = 0;
        int day = 1;
        while (!pq.empty()) {
            const auto [i, j, price] = pq.top();
            pq.pop();
            result += price * day;
            if (j >= 1) {
                pq.emplace(i, j - 1, values[i][j - 1]);
            }
            day++;
        }
        return result;
    }
};