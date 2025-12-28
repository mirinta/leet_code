#include <string>
#include <vector>

/**
 * 给定一个数字，我们按照如下规则把它翻译为字符串：
 *
 * 0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。
 *
 * 一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
 *
 * ! 0 <= num < 2^31
 */

class Solution {
public:
    int translateNum(int num)
    {
        return approach2(num);
    }

private:
    int approach2(int num)
    {
        // DP with space optimization
        const std::string s = std::to_string(num);
        const int n = s.size();
        int iMinus1 = 1;
        int iMinus2 = 1;
        for (int i = 2; i <= n; ++i) {
            int temp = iMinus1;
            if (s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] <= '5') {
                temp += iMinus2;
            }
            iMinus2 = iMinus1;
            iMinus1 = temp;
        }
        return iMinus1;
    }

    int approach1(int num)
    {
        // dp[i] = num of translations of s[0:i)
        const std::string s = std::to_string(num);
        const int n = s.size();
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            dp[i] = dp[i - 1];
            if (s[i - 2] == '1' || s[i - 2] == '2' && s[i - 1] <= '5') {
                dp[i] += dp[i - 2];
            }
        }
        return dp[n];
    }
};