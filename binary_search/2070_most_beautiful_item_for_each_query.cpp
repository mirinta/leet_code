#include <algorithm>
#include <vector>

/**
 * You are given a 2D integer array items where items[i] = [pricei, beautyi] denotes the price and
 * beauty of an item respectively.
 *
 * You are also given a 0-indexed integer array queries. For each queries[j], you want to determine
 * the maximum beauty of an item whose price is less than or equal to queries[j]. If no such item
 * exists, then the answer to this query is 0.
 *
 * Return an array answer of the same length as queries where answer[j] is the answer to the jth
 * query.
 *
 * ! 1 <= items.length, queries.length <= 10^5
 * ! items[i].length == 2
 * ! 1 <= pricei, beautyi, queries[j] <= 10^9
 */

class Solution
{
public:
    std::vector<int> maximumBeauty(std::vector<std::vector<int>>& items, std::vector<int>& queries)
    {
        std::sort(items.begin(), items.end(),
                  [](const auto& item1, const auto& item2) { return item1[0] < item2[0]; });
        std::vector<int> maxBeauty(items.size(), items[0][1]);
        for (int i = 1; i < items.size(); ++i) {
            maxBeauty[i] = std::max(maxBeauty[i - 1], items[i][1]);
        }
        std::vector<int> result(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            auto iter = std::upper_bound(items.begin(), items.end(), queries[i],
                                         [](int val, const auto& item) { return item[0] > val; });
            if (iter == items.begin()) {
                result[i] = 0;
            } else {
                result[i] = maxBeauty[std::prev(iter) - items.begin()];
            }
        }
        return result;
    }
};