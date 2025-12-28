/**
 * Given 3 positive numbers "a", "b", and "c". Return the minimum flips required in some bits of "a"
 * and "b" to make ("a" OR "b" == "c").
 *
 * Flip operation consists of change any single bit 1 to 0 or change the bit 0 to 1 in their binary
 * representations.
 *
 * ! 1 <= a <= 10^9
 * ! 1 <= b <= 10^9
 * ! 1 <= c <= 10^9
 */

class Solution {
public:
    int minFlips(int a, int b, int c)
    {
        if ((a | b) == c)
            return 0;

        const int OR = a | b;
        const int XOR = a ^ b;
        int result = 0;
        for (int i = 0; i < 32; ++i) {
            if (((OR >> i) & 1) == ((c >> i) & 1))
                continue;

            if ((c >> i) & 1) {
                result++;
            } else {
                result += 2 - ((XOR >> i) & 1);
            }
        }
        return result;
    }
};