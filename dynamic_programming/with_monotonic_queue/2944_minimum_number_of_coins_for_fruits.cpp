#include <array>
#include <deque>
#include <vector>

/**
 * You are at a fruit market with different types of exotic fruits on display.
 *
 * You are given a 1-indexed array prices, where prices[i] denotes the number of coins needed to
 * purchase the ith fruit.
 *
 * The fruit market has the following offer:
 *
 * If you purchase the ith fruit at prices[i] coins, you can get the next i fruits for free.
 * Note that even if you can take fruit j for free, you can still purchase it for prices[j] coins to
 * receive a new offer.
 *
 * Return the minimum number of coins needed to acquire all the fruits.
 *
 * ! 1 <= prices.length <= 1000
 * ! 1 <= prices[i] <= 10^5
 */

class Solution {
public:
    int minimumCoins(std::vector<int>& prices)
    {
        return approach2(prices);
    }

private:
    // DP + Monotonic Queue, time O(N), space O(N)
    int approach2(std::vector<int>& prices)
    {
        const int n = prices.size();
        std::vector<std::array<int, 2>> dp(n + 1, {INT_MAX, INT_MAX});
        dp[0] = {0, 0};
        std::deque<int> deque; // store indices of dp
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = prices[i - 1] + std::min(dp[i - 1][0], dp[i - 1][1]);
            while (!deque.empty() && i > 2 * deque.front()) {
                deque.pop_front();
            }
            if (!deque.empty()) {
                dp[i][0] = dp[deque.front()][1];
            }
            while (!deque.empty() && dp[i][1] < dp[deque.back()][1]) {
                deque.pop_back();
            }
            deque.push_back(i);
        }
        return std::min(dp[n][0], dp[n][1]);
    }

    // DP, time O(N^2), space O(N)
    int approach1(std::vector<int>& prices)
    {
        const int n = prices.size();
        // dp[i][0] = min cost to get fruits[0:i) while the ith fruit is not paid
        // dp[i][1] = min cost to get fruits[0:i) while the ith fruit is paid
        // X X X j j+1 X X X X X X i
        //         |<---j fruits-->|
        std::vector<std::array<int, 2>> dp(n + 1, {INT_MAX, INT_MAX});
        dp[0] = {0, 0};
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = prices[i - 1] + std::min(dp[i - 1][0], dp[i - 1][1]);
            for (int j = i - 1; i <= 2 * j; --j) {
                dp[i][0] = std::min(dp[i][0], dp[j][1]);
            }
        }
        return std::min(dp[n][0], dp[n][1]);
    }
};