#include <cmath>

/**
 * We build a table of n rows (1-indexed). We start by writing 0 in the 1st row. Now in every
 * subsequent row, we look at the previous row and replace each occurrence of 0 with 01, and each
 * occurrence of 1 with 10.
 *
 * - For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the 3rd row is 0110.
 *
 * Given two integer n and k, return the kth (1-indexed) symbol in the nth row of a table of n rows.
 *
 * ! 1 <= n <= 30
 * ! 1 <= k <= 2^(n - 1)
 */

#include <cmath>

class Solution {
public:
    int kthGrammar(int n, int k)
    {
        /**
         *       k:   (1)     (2)
         * row i-1:    0       1
         *            / \     / \
         *   row i:  0   1   1   0
         *       k: (1) (2) (3) (4)
         *
         * the kth symbol in the ith row comes from the ceil(k/2)th symbol in the i-1th row
         *
         * let src = the ceil(k/2)th symbol in the i-1th row
         * - if k is odd and src = 0, then result = 0
         * - if k is even and src = 0, then result = 1
         * - if k is odd and src = 1, then result = 1
         * - if k is even and src = 1, then result = 0
         */
        if (n == 1)
            return 0;

        const int src = kthGrammar(n - 1, std::ceil(k * 0.5));
        return k % 2 != 0 ? src : 1 - src;
    }
};
