#include <vector>

/**
 * You are given an integer array prices representing the daily price history of a stock, where
 * prices[i] is the stock price on the ith day.
 *
 * A smooth descent period of a stock consists of one or more contiguous days such that the price on
 * each day is lower than the price on the preceding day by exactly 1. The first day of the period
 * is exempted from this rule.
 *
 * Return the number of smooth descent periods.
 *
 * ! 1 <= prices.length <= 10^5
 * ! 1 <= prices[i] <= 10^5
 */

class Solution {
public:
    long long getDescentPeriods(std::vector<int>& prices)
    {
        const int n = prices.size();
        long long result = 0;
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && prices[j - 1] - prices[j] == 1) {
                j++;
            }
            result += 1LL * (j - i + 1) * (j - i) / 2;
            i = j;
        }
        return result;
    }
};