#include <vector>

/**
 * You are given two non-negative integer arrays price and tastiness, both arrays have the same
 * length n. You are also given two non-negative integers maxAmount and maxCoupons.
 *
 * For every integer i in range [0, n - 1]:
 *
 * - price[i] describes the price of ith fruit.
 *
 * - tastiness[i] describes the tastiness of ith fruit.
 *
 * You want to purchase some fruits such that total tastiness is maximized and the total price does
 * not exceed maxAmount.
 *
 * Additionally, you can use a coupon to purchase fruit for half of its price (rounded down to the
 * closest integer). You can use at most maxCoupons of such coupons.
 *
 * Return the maximum total tastiness that can be purchased.
 *
 * Note that:
 *
 * - You can purchase each fruit at most once.
 *
 * - You can use coupons on some fruit at most once.
 *
 * ! n == price.length == tastiness.length
 * ! 1 <= n <= 100
 * ! 0 <= price[i], tastiness[i], maxAmount <= 1000
 * ! 0 <= maxCoupons <= 5
 */

class Solution {
public:
    int maxTastiness(std::vector<int>& price, std::vector<int>& tastiness, int maxAmount, int maxCoupons)
    {
        // dp[i][j][k] = max total tastiness of buying fruits[0:i-1] while the total cost is j and
        // the num of used coupons is k
        const int n = price.size();
        std::vector<std::vector<std::vector<int>>> dp(
            n + 1, std::vector<std::vector<int>>(1 + maxAmount, std::vector<int>(maxCoupons + 1, 0)));
        int result = 0;
        for (int i = 1; i <= n; ++i) {
            const int cost = price[i - 1];
            const int halfCost = cost / 2;
            const int gain = tastiness[i - 1];
            for (int j = 0; j <= maxAmount; ++j) {
                for (int k = 0; k <= maxCoupons; ++k) {
                    // case 1: skip current fruit
                    dp[i][j][k] = dp[i - 1][j][k];
                    // case 2: buy current fruit without using coupon
                    if (j - cost >= 0) {
                        dp[i][j][k] = std::max(dp[i][j][k], gain + dp[i - 1][j - cost][k]);
                    }
                    // case 3: buy current fruit using coupon
                    if (k > 0 && j - halfCost >= 0) {
                        dp[i][j][k] = std::max(dp[i][j][k], gain + dp[i - 1][j - halfCost][k - 1]);
                    }
                    result = std::max(result, dp[i][j][k]);
                }
            }
        }
        return result;
    }
};