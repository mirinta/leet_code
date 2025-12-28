#include <vector>

/**
 * 三步问题。有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶或3阶。实现一种方法，计算小孩有多少种上楼梯的方式。结果可能很大，你需要对结果模1000000007。
 *
 * ! n范围在[1, 1000000]之间
 */

class Solution {
public:
    int waysToStep(int n)
    {
        return approach2(n);
    }

private:
    static constexpr int kMod = 1e9 + 7;

    int approach2(int n)
    {
        if (n <= 2)
            return n;

        int iMinus1 = 2;
        int iMinus2 = 1;
        int iMinus3 = 1;
        for (int i = 3; i <= n; ++i) {
            const int dp = ((iMinus1 + iMinus2) % kMod + iMinus3) % kMod;
            std::swap(iMinus3, iMinus2);
            std::swap(iMinus2, iMinus1);
            iMinus1 = dp;
        }
        return iMinus1;
    }

    int approach1(int n)
    {
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            dp[i] = (dp[i] + dp[i - 1]) % kMod;
            if (i >= 2) {
                dp[i] = (dp[i] + dp[i - 2]) % kMod;
            }
            if (i >= 3) {
                dp[i] = (dp[i] + dp[i - 3]) % kMod;
            }
        }
        return dp[n];
    }
};