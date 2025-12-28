/**
 * You are given two integers num1 and num2.
 *
 * In one operation, you can choose integer i in the range [0, 60] and subtract 2i + num2 from num1.
 *
 * Return the integer denoting the minimum number of operations needed to make num1 equal to 0.
 *
 * If it is impossible to make num1 equal to 0, return -1.
 *
 * ! 1 <= num1 <= 10^9
 * ! -10^9 <= num2 <= 10^9
 */

class Solution {
public:
    int makeTheIntegerZero(int num1, int num2)
    {
        // let x = num1, y = num2
        // x1 = x - (2^i1 + y)
        // x2 = x - (2^i1 + y) - (2^i2 + y)
        // ..., assume we make x equal to 0 in the nth round
        // xn = 0 = x - ny - sum(2^i1, ..., 2^in)
        // then, we have:
        // x = ny + k, where k = sum(2^i1, ..., 2^in)
        // - x > 0, according to the constraints
        // - n > 0, it is the number of operations we want to minimize
        // - k >= n, because i1,...in are in range [0,60], ----------------------- #Condition1#
        // - therefore, x > y, --------------------------------------------------- #Condition2#
        // then, we check each n starting from 1, because we want to minimize it
        // - k = x - ny = sum(2^i1, ..., 2^in)
        // - count the number of ones in k's binary representation,
        //   if it is greater than n, then k can be the sum of many 2^i ---------- #Condition3#
        if (num2 >= num1)
            return -1;

        long long n = 1;
        while (true) {
            const long long k = num1 - n * num2;
            if (k <= 0)
                return -1;

            if (numOfBinaryOnes(k) <= n && n <= k)
                break;

            n++;
        }
        return n;
    }

private:
    int numOfBinaryOnes(long long val)
    {
        int count = 0;
        while (val) {
            val &= (val - 1);
            count++;
        }
        return count;
    }
};