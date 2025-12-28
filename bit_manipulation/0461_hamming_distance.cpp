/**
 * The Hamming distance between two integers is the number of positions at which the corresponding
 * bits are different.
 *
 * Given two integers x and y, return the Hamming distance between them.
 *
 * ! 0 <= x, y <= 231 - 1
 */

class Solution {
public:
    int hammingDistance(int x, int y)
    {
        int XOR = x ^ y;
        int result = 0;
        while (XOR) {
            result++;
            XOR &= XOR - 1;
        }
        return result;
    }
};