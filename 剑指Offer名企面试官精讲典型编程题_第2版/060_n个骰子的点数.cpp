#include <vector>

/**
 * 把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。
 *
 * 你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i
 * 小的那个的概率。
 *
 * ! 1 <= n <= 11
 */

class Solution {
public:
    std::vector<double> dicesProbability(int n)
    {
        // dp[i][j] = prob of value j rolling i dices
        constexpr double kProb = 1.0 / 6;
        std::vector<std::vector<double>> dp(n + 1, std::vector<double>(6 * n + 1, 0));
        for (int j = 1; j <= 6; ++j) {
            dp[1][j] = kProb;
        }
        for (int i = 2; i <= n; ++i) {
            for (int j = 2; j <= 6 * i; ++j) {
                double sum = 0;
                // make sure j - k >= 1, and k <= 6
                for (int k = 1; k <= std::min(6, j - 1); ++k) {
                    sum += dp[i - 1][j - k];
                }
                dp[i][j] = sum * kProb;
            }
        }
        // the min value of rolling n dices is n
        return {dp[n].begin() + n, dp[n].end()};
    }
};
