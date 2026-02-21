/**
 * Given two integers left and right, return the count of numbers in the inclusive range [left, right] having a prime
 * number of set bits in their binary representation.
 *
 * Recall that the number of set bits an integer has is the number of 1's present when written in binary.
 *
 * - For example, 21 written in binary is 10101, which has 3 set bits.
 *
 * ! 1 <= left <= right <= 10^6
 * ! 0 <= right - left <= 10^4
 */

class Solution {
public:
    int countPrimeSetBits(int left, int right)
    {
        int result = 0;
        while (left <= right) {
            result += isPrime(setbits(left));
            left++;
        }
        return result;
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

    bool isPrime(int n)
    {
        return n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13 || n == 17 || n == 19 || n == 23 || n == 29;
    }
};