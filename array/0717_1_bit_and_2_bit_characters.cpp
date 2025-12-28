#include <vector>

/**
 * We have two special characters:
 *
 * The first character can be represented by one bit 0.
 *
 * The second character can be represented by two bits (10 or 11).
 *
 * Given a binary array bits that ends with 0, return true if the last character must be a one-bit
 * character.
 *
 * ! 1 <= bits.length <= 1000
 * ! bits[i] is either 0 or 1.
 */

class Solution {
public:
    bool isOneBitCharacter(std::vector<int>& bits)
    {
        const int n = bits.size();
        int i = 0;
        while (i < n - 1) {
            i += bits[i] + 1;
        }
        return i == n - 1;
    }
};
