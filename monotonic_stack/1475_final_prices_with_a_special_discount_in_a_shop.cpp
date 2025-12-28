#include <stack>
#include <vector>

/**
 * You are given an integer array prices where prices[i] is the price of the ith item in a shop.
 *
 * There is a special discount for items in the shop. If you buy the ith item, then you will receive
 * a discount equivalent to prices[j] where j is the minimum index such that j > i and prices[j] <=
 * prices[i]. Otherwise, you will not receive any discount at all.
 *
 * Return an integer array answer where answer[i] is the final price you will pay for the ith item
 * of the shop, considering the special discount.
 *
 * ! 1 <= prices.length <= 500
 * ! 1 <= prices[i] <= 1000
 */

class Solution {
public:
    std::vector<int> finalPrices(std::vector<int>& prices)
    {
        const int n = prices.size();
        const auto nextSmallerOrEqual = getNextSmallerOrEqual(prices);
        std::vector<int> result(n);
        for (int i = 0; i < n; ++i) {
            const int j = nextSmallerOrEqual[i];
            result[i] = prices[i] - (j == -1 ? 0 : prices[j]);
        }
        return result;
    }

private:
    std::vector<int> getNextSmallerOrEqual(std::vector<int>& prices)
    {
        const int n = prices.size();
        std::stack<int> stack;
        std::vector<int> result(n, -1);
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && prices[i] < prices[stack.top()]) {
                stack.pop();
            }
            result[i] = stack.empty() ? -1 : stack.top();
            stack.push(i);
        }
        return result;
    }
};