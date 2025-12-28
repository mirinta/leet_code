#include <vector>

/**
 * 给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），
 * 每段绳子的长度记为 k[0],k[1]...k[m-1] 。
 *
 * 请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
 *
 * 答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
 *
 * 例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
 *
 * ! 2 <= n <= 1000
 *
 * ! 本题与LC 343相同。
 */

class Solution {
public:
    int cuttingRope(int n)
    {
        // Greedy
        if (n < 2)
            return 0;

        if (n == 2)
            return 1; // 1x1

        if (n == 3)
            return 2; // 1x2

        if (n == 4)
            return 4; // 2x2

        // consider n >= 5
        // - cut it into pieces with length 3, as much as possible
        // - #NOTE#, if length <= 4, we don't cut the rope
        constexpr int kMod = 1e9 + 7;
        long long result = 1;
        while (n > 4) {
            result = result * 3 % kMod;
            n -= 3;
        }
        result = result * n % kMod;
        return result;
    }
};
