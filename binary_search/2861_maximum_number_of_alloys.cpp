#include <vector>

/**
 * You are the owner of a company that creates alloys using various types of metals. There are n
 * different types of metals available, and you have access to k machines that can be used to create
 * alloys. Each machine requires a specific amount of each metal type to create an alloy.
 *
 * For the ith machine to create an alloy, it needs composition[i][j] units of metal of type j.
 * Initially, you have stock[i] units of metal type i, and purchasing one unit of metal type i costs
 * cost[i] coins.
 *
 * Given integers n, k, budget, a 1-indexed 2D array composition, and 1-indexed arrays stock and
 * cost, your goal is to maximize the number of alloys the company can create while staying within
 * the budget of budget coins.
 *
 * All alloys must be created with the same machine.
 *
 * Return the maximum number of alloys that the company can create.
 *
 * ! 1 <= n, k <= 100
 * ! 0 <= budget <= 108
 * ! composition.length == k
 * ! composition[i].length == n
 * ! 1 <= composition[i][j] <= 100
 * ! stock.length == cost.length == n
 * ! 0 <= stock[i] <= 108
 * ! 1 <= cost[i] <= 100
 */

class Solution {
public:
    int maxNumberOfAlloys(int n,
                          int k,
                          int budget,
                          std::vector<std::vector<int>>& composition,
                          std::vector<int>& stock,
                          std::vector<int>& cost)
    {
        int min = 0;
        int max = INT_MAX;
        while (min < max) {
            const long long production = max - (max - min) / 2;
            if (isValid(production, budget, composition, stock, cost)) {
                min = production;
            } else {
                max = production - 1;
            }
        }
        return max;
    }

private:
    bool isValid(long long production,
                 long long budget,
                 const std::vector<std::vector<int>>& composition,
                 const std::vector<int>& stock,
                 const std::vector<int>& cost)
    {
        const int n = stock.size();
        std::vector<long long> needs(n);
        for (const auto& metals : composition) {
            std::fill(needs.begin(), needs.end(), 0);
            for (int i = 0; i < n; ++i) {
                needs[i] = production * metals[i];
            }
            long long sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += cost[i] * std::max(0LL, needs[i] - stock[i]);
            }
            if (sum <= budget)
                return true;
        }
        return false;
    }
};