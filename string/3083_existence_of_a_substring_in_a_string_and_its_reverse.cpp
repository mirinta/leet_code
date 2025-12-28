#include <string>

/**
 * Given a string s, find any substring of length 2 which is also present in the reverse of s.
 *
 * Return true if such a substring exists, and false otherwise.
 *
 * ! 1 <= s.length <= 100
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    bool isSubstringPresent(std::string s)
    {
        const int n = s.size();
        const std::string reversed(s.rbegin(), s.rend());
        for (int i = 0; i + 1 < n; ++i) {
            if (reversed.find(s.substr(i, 2)) != std::string::npos)
                return true;
        }
        return false;
    }
};