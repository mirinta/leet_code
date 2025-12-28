#include <vector>

/**
 * Write a function that reverses a string. The input string is given as an array of characters s.
 *
 * You must do this by modifying the input array in-place with O(1) extra memory.
 *
 * ! 1 <= s.length <= 10^5
 * ! s[i] is a printable ascii character.
 */

class Solution {
public:
    void reverseString(std::vector<char>& s)
    {
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) {
            std::swap(s[i], s[j]);
        }
    }
};