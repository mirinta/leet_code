#include <cmath>

/**
 * Given an integer n, return true if and only if it is an Armstrong number.
 *
 * The k-digit number n is an Armstrong number if and only if the kth power of each digit sums to n.
 *
 * ! 1 <= n <= 10^8
 */

class Solution {
public:
    bool isArmstrong(int n)
    {
        const int k = numOfDigits(n);
        int val = n;
        int sum = 0;
        while (val) {
            sum += std::pow(val % 10, k);
            val /= 10;
        }
        return sum == n;
    }

private:
    int numOfDigits(int n)
    {
        int count = 0;
        while (n) {
            count++;
            n /= 10;
        }
        return count;
    }
};