#include <vector>

/**
 * 硬币。给定数量不限的硬币，币值为25分、10分、5分和1分，编写代码计算n分有几种表示法。(结果可能会很大，你需要将结果模上1000000007)
 *
 * ! 0 <= n (总金额) <= 1000000
 */

class Solution {
public:
    int waysToChange(int amount)
    {
        return approach2(amount);
    }

private:
    static constexpr int kMod = 1e9 + 7;
    const std::vector<int> coins{1, 5, 10, 25};

    int approach2(int amount)
    {
        if (amount == 0)
            return 0;

        const int n = coins.size();
        std::vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (coins[i - 1] > j)
                    continue;

                dp[j] = (dp[j] + dp[j - coins[i - 1]]) % kMod;
            }
        }
        return dp[amount];
    }

    int approach1(int amount)
    {
        if (amount == 0)
            return 0;

        // dp[i][j] = num of ways to make up amount j using coins[0:i]
        const int n = coins.size();
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= amount; ++j) {
                if (coins[i - 1] > j) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = (dp[i - 1][j] + dp[i][j - coins[i - 1]]) % kMod;
                }
            }
        }
        return dp[n][amount];
    }
};