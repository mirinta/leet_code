/**
 * You are given a positive integer n. Determine whether n is divisible by the sum of the following two values:
 *
 * The digit sum of n (the sum of its digits).
 *
 * The digit product of n (the product of its digits).
 *
 * Return true if n is divisible by this sum; otherwise, return false.
 *
 * ! 1 <= n <= 10^6
 */

class Solution {
public:
    bool checkDivisibility(int n)
    {
        return n % helper(n) == 0;
    }

private:
    int helper(int n)
    {
        if (n == 0)
            return 0;

        int sum = 0;
        int product = 1;
        while (n) {
            const int d = n % 10;
            sum += d;
            product *= d;
            n /= 10;
        }
        return sum + product;
    }
};