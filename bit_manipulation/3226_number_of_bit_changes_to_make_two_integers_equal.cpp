/**
 * You are given two positive integers n and k.
 *
 * You can choose any bit in the binary representation of n that is equal to 1 and change it to 0.
 *
 * Return the number of changes needed to make n equal to k. If it is impossible, return -1.
 *
 * ! 1 <= n, k <= 10^6
 */

class Solution {
public:
    int minChanges(int n, int k)
    {
        const int XOR = n ^ k;
        if (XOR != (n & XOR))
            return -1;

        return numOfSetBits(XOR);
    }

private:
    int numOfSetBits(int n)
    {
        int result = 0;
        while (n) {
            result++;
            n &= n - 1;
        }
        return result;
    }
};