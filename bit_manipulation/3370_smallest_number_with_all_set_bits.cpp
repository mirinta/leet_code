/**
 * You are given a positive number n.
 *
 * Return the smallest number x greater than or equal to n, such that the binary representation of x
 * contains only set bits.
 *
 * ! 1 <= n <= 1000
 */

class Solution {
public:
    int smallestNumber(int n)
    {
        return (1 << numOfBits(n)) - 1;
    }

private:
    int numOfBits(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n >>= 1;
        }
        return result;
    }
};