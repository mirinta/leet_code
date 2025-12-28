#include <vector>

/**
 * 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），
 * 每段绳子的长度记为 k[0],k[1]...k[m-1] 。
 *
 * 请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
 *
 * 例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
 *
 * ! 2 <= n <= 58
 *
 * ! 本题与LC 343相同。
 */

class Solution {
public:
    int cuttingRope(int n)
    {
        // DP
        // dp[i] = max product of cutting a rope with length i into at leaset two parts
        // base case: dp[0] = dp[1] = 0, dp[2] = 1
        std::vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; ++i) {
            // cutting position:
            // 0 1 ... j ... i-1 i
            // if the cutting position is j,
            // the two parts are [0...j] and [j...i]
            for (int j = 1; j <= i / 2; ++j) {
                dp[i] = std::max({dp[i], j * (i - j), j * dp[i - j]});
            }
        }
        return dp[n];
    }
};