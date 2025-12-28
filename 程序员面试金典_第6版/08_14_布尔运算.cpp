#include <array>
#include <string>
#include <vector>

/**
 * 给定一个布尔表达式和一个期望的布尔结果 result，布尔表达式由 0 (false)、1 (true)、& (AND)、 | (OR)
 * 和 ^ (XOR) 符号组成。实现一个函数，算出有几种可使该表达式得出 result 值的括号方法。
 *
 * ! 运算符的数量不超过 19 个
 */

class Solution {
public:
    int countEval(std::string s, int result)
    {
        // dp[i][j][0] = num of ways that expression s[i:j] can be evaluated to be 0
        // dp[i][j][1] = num of ways that expression s[i:j] can be evaluated to be 1
        const int n = s.size();
        std::vector<std::vector<std::array<int, 2>>> dp(n, std::vector<std::array<int, 2>>(n, {0, 0}));
        for (int i = 0; i < n; ++i) {
            if (s[i] == '0' || s[i] == '1') {
                dp[i][i][s[i] - '0'] = 1;
            }
        }
        for (int length = 2; length <= n; ++length) {
            for (int i = 0; i + length - 1 < n; ++i) {
                const int j = i + length - 1;
                if (!std::isdigit(s[i]) || !std::isdigit(s[j]))
                    continue;

                // s[k] is an operator
                for (int k = i + 1; k <= j - 1; k += 2) {
                    switch (s[k]) {
                        case '&':
                            dp[i][j][0] += dp[i][k - 1][0] * dp[k + 1][j][1] + dp[i][k - 1][1] * dp[k + 1][j][0] +
                                           dp[i][k - 1][0] * dp[k + 1][j][0];
                            dp[i][j][1] += dp[i][k - 1][1] * dp[k + 1][j][1];
                            break;
                        case '|':
                            dp[i][j][0] += dp[i][k - 1][0] * dp[k + 1][j][0];
                            dp[i][j][1] += dp[i][k - 1][1] * dp[k + 1][j][0] + dp[i][k - 1][0] * dp[k + 1][j][1] +
                                           dp[i][k - 1][1] * dp[k + 1][j][1];
                            break;
                        case '^':
                            dp[i][j][0] += dp[i][k - 1][0] * dp[k + 1][j][0] + dp[i][k - 1][1] * dp[k + 1][j][1];
                            dp[i][j][1] += dp[i][k - 1][1] * dp[k + 1][j][0] + dp[i][k - 1][0] * dp[k + 1][j][1];
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        return dp[0][n - 1][result];
    }
};