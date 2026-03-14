
/**
 * You are given a positive integer n, you can do the following operation any number of times:
 *
 * - Add or subtract a power of 2 from n.
 *
 * Return the minumum number of operations to make n equal to 0.
 *
 * A number x is power of 2 if x == 2^i where i >= 0.
 *
 * ! 1 <= n <= 10^5
 */

class Solution {
public:
    int minOperations(int n)
    {
        // 39 = 100111
        // 54 = 110110
        int result = 0;
        for (int i = 0; i < 31; ++i) {
            const int opt = n + (1 << i);
            if (setbits(opt) + 1 <= setbits(n)) {
                n = opt;
                result++;
            }
        }
        return result + setbits(n);
    }

private:
    int setbits(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};