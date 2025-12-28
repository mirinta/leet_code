#include <vector>

/**
 * You are given two positive integers x and y.
 *
 * In one operation, you can do one of the four following operations:
 *
 * - Divide x by 11 if x is a multiple of 11.
 *
 * - Divide x by 5 if x is a multiple of 5.
 *
 * - Decrement x by 1.
 *
 * - Increment x by 1.
 *
 * Return the minimum number of operations required to make x and y equal.
 *
 * ! 1 <= x, y <= 10^4
 */

class Solution {
public:
    int minimumOperationsToMakeEqual(int x, int y)
    {
        memo.resize(x + 1);
        std::fill(memo.begin(), memo.end(), -1);
        return dp(x, y);
    }

private:
    std::vector<int> memo;

    int dp(int x, int y)
    {
        // op1: /11
        // op2: /5
        // op3: -1
        // op4: +1
        if (x == y)
            return 0;

        if (x < y)
            return y - x; // op4

        if (memo[x] != -1)
            return memo[x];

        const int case1 = x - y;                                 // op3
        const int case2 = 1 + x % 5 + dp(x / 5, y);              // x>=5, op2 and op3
        const int case3 = 1 + (5 - x % 5) + dp(x / 5 + 1, y);    // x<5, op2 and op4
        const int case4 = 1 + x % 11 + dp(x / 11, y);            // x>=11, op1 and op3
        const int case5 = 1 + (11 - x % 11) + dp(x / 11 + 1, y); // x<11, op1 and op4
        return memo[x] = std::min({case1, case2, case3, case4, case5});
    }
};