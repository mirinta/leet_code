#include <vector>

/**
 * Given n orders, each order consist in pickup and delivery services.
 *
 * Count all valid pickup/delivery possible sequences such that delivery(i) is always after of
 * pickup(i).
 *
 * Since the answer may be too large, return it modulo 10^9 + 7.
 *
 * ! 1 <= n <= 500
 */

class Solution {
public:
    int countOrders(int n)
    {
        // f(i) = the num of all valid sequences of i orders
        // assume f(i-1) is calculated, it is sequence of length L=2(i-1),
        // and there're L+1 empty spaces to place new items
        // _ X _ X _ X _ X _ X _ X _
        // case1: choose of one of the empty space and place Pi and Di together
        // - num of ways of case1 = C(L+1,1)=L+1=2(i-1)+1
        // case2: choose one of the empty space and place Pi, then choose another space and place Di
        // - num of ways of case2 = C(L+1,2)=(L+1)L/2=(2(i-1)+1)*(i-1)
        // thus, num of ways of the ith order = f(i-1)*(case1+case2)
        static constexpr int kMod = 1e9 + 7;
        std::vector<long long> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            const long long case1 = 2 * (i - 1) + 1;
            const long long case2 = (2 * (i - 1) + 1) * (i - 1);
            dp[i] = dp[i - 1] * (case1 + case2) % kMod;
        }
        return dp[n];
    }
};