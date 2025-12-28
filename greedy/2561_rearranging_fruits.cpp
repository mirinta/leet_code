#include <algorithm>
#include <unordered_map>
#include <vector>

/**
 * You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays
 * basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets
 * equal. To do so, you can use the following operation as many times as you want:
 *
 * Chose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
 * The cost of the swap is min(basket1[i],basket2[j]).
 * Two baskets are considered equal if sorting them according to the fruit cost makes them exactly
 * the same baskets.
 *
 * Return the minimum cost to make both the baskets equal or -1 if impossible.
 *
 * ! basket1.length == basket2.length
 * ! 1 <= basket1.length <= 10^5
 * ! 1 <= basket1[i],basket2[i] <= 10^9
 */

class Solution {
public:
    long long minCost(std::vector<int>& basket1, std::vector<int>& basket2)
    {
        const int n = basket1.size();
        std::unordered_map<int, std::pair<int, int>> map;
        for (int i = 0; i < n; ++i) {
            map[basket1[i]].first++;
            map[basket2[i]].second++;
        }
        int min = INT_MAX;
        std::vector<int> move;
        for (const auto& [v, counts] : map) {
            min = std::min(v, min);
            const auto& [count1, count2] = counts;
            if (count1 == count2)
                continue;

            if ((count1 + count2) % 2)
                return -1;

            const int target = (count1 + count2) / 2;
            move.insert(move.end(), std::abs(target - count1), v);
        }
        std::sort(move.begin(), move.end());
        long long result = 0;
        for (int i = 0; i < move.size() / 2; ++i) {
            result += std::min(2 * min, move[i]);
        }
        return result;
    }
};