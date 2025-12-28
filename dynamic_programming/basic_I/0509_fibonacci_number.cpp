#include <vector>

/**
 * The Fibonacci numbers, commonly denoted F(n) from a sequence, called the Fibonacci sequence, such
 * that each number is the num of the two preceding ones, starting from 0 and 1. That is,
 *
 * F(0) = 0, F(1) = 1
 * F(n) = F(n - 1) + F(n - 2), for n > 1.
 *
 * Given "n", calculate F(n).
 */

class Solution {
public:
    int fib(int n)
    {
        // approach 1: naive recursion
        // there are a lot of duplicate calculations during the recursion,
        // e.g., f(n) = f(n-1) + f(n-2), f(n-1) = f(n-2) + f(n-3), f(n-2) is calculated twice
        // if (n == 0 || n == 1)
        //     return n;
        // return fib(n - 1) + fib(n - 2);
        // ------------------------------
        // approach 2: dynamic programming
        // to calculate f(n), we need f(n-1), f(n-2), ..., f(1), f(0)
        // we can store these intermediate results in a container
        // if (n < 2)
        //     return n;

        // std::vector<int> table(n + 1, 0);
        // table[1] = 1;
        // for (size_t i = 2; i <= n; ++i) {
        //     table[i] = table[i - 1] + table[i - 2];
        // }
        // return table[n];
        // ------------------------------
        // approach 3: optimization
        // in fact, we only need two intermediate results, f(n-1) and f(n-2)
        if (n < 2)
            return n;

        int fn_2 = 0; // f(n-2)
        int fn_1 = 1; // f(n-1)
        for (int i = 2; i <= n; ++i) {
            int fn = fn_1 + fn_2;
            fn_2 = fn_1;
            fn_1 = fn;
        }
        return fn_1;
    }
};