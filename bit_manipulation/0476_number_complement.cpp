
/**
 * The complement of an integer is the integer you get when you flip all the 0's to 1's and all the
 * 1's to 0's in its binary representation.
 *
 * For example, The integer 5 is "101" in binary and its complement is "010" which is the integer 2.
 * Given an integer num, return its complement.
 *
 * ! 1 <= num < 2^31
 *
 * ! This question is the same as LC.1009.
 */

class Solution {
public:
    int findComplement(int num)
    {
        const int bits = numOfBits(num);
        return num ^ ((1LL << bits) - 1);
    }

private:
    int numOfBits(int num)
    {
        int result = 0;
        while (num) {
            result++;
            num >>= 1;
        }
        return result;
    }
};