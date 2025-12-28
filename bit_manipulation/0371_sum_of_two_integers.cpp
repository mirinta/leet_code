/**
 * Given two integers a and b, return the sum of the two integers without using the operators + and
 * -.
 *
 * ! -1000 <= a, b <= 1000
 */

class Solution {
public:
    int getSum(int a, int b)
    {
        if (a == 0 || b == 0)
            return a == 0 ? b : a;

        return getSum(a ^ b, unsigned(a & b) << 1);
    }
};