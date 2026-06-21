#include <vector>

/**
 * It is sweltering summer day, and a boy wants to buy some ice cream bars.
 *
 * At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of
 * the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many as ice cream
 * bars as possible.
 *
 * Note: The boy can buy the ice cream bars in any order.
 *
 * Return the maximum number of ice cream bars the boy can buy with coins coins.
 *
 * You must solve the problem by counting sort.
 *
 * ! costs.length == n
 * ! 1 <= n <= 10^5
 * ! 1 <= costs[i] <= 10^5
 * ! 1 <= coins <= 10^8
 */

class Solution {
public:
    int maxIceCream(std::vector<int>& costs, int coins)
    {
        int min = INT_MAX;
        int max = INT_MIN;
        for (const auto& c : costs) {
            min = std::min(min, c);
            max = std::max(max, c);
        }
        if (min > coins)
            return 0;

        std::vector<int> count(max + 1, 0);
        for (const auto& c : costs) {
            count[c]++;
        }
        int result = 0;
        for (int cost = 0; cost <= max; ++cost) {
            if (count[cost] == 0)
                continue;

            if (cost > coins)
                break;

            const int toBuy = std::min(count[cost], coins / cost);
            result += toBuy;
            coins -= toBuy * cost;
        }
        return result;
    }
};