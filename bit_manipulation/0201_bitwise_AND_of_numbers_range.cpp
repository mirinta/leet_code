/**
 * Given two integers left and right that represent the range [left, right], return the bitwise AND
 * of all numbers in this range, inclusive.
 *
 * ! 0 <= left <= right <= 2^31 - 1
 */

class Solution {
public:
    int rangeBitwiseAnd(int left, int right)
    {
        // find the longest common prefix
        int numOfShifts = 0;
        while (left != right) {
            numOfShifts++;
            left >>= 1;
            right >>= 1;
        }
        return left << numOfShifts;
    }
};
