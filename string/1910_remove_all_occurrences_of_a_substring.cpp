#include <string>

/**
 * Given two strings s and part, perform the following operation on s until all occurrences of the
 * substring part are removed:
 *
 * - Find the leftmost occurrence of the substring part and remove it from s.
 *
 * Return s after removing all occurrences of part.
 *
 * A substring is a contiguous sequence of characters in a string.
 *
 * ! 1 <= s.length <= 1000
 * ! 1 <= part.length <= 1000
 * ! s​​​​​​ and part consists of lowercase English letters.
 */

class Solution {
public:
    std::string removeOccurrences(std::string s, std::string part)
    {
        const int n = part.size();
        while (s.size() >= n) {
            const int i = s.find(part);
            if (i == std::string::npos)
                break;

            s.erase(i, n);
        }
        return s;
    }
};