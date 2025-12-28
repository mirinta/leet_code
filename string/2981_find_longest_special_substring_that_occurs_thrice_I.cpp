#include <string>
#include <unordered_map>

/**
 * You are given a string s that consists of lowercase English letters.
 *
 * A string is called special if it is made up of only a single character. For example, the string
 * "abc" is not special, whereas the strings "ddd", "zz", and "f" are special.
 *
 * Return the length of the longest special substring of s which occurs at least thrice, or -1 if no
 * special substring occurs at least thrice.
 *
 * A substring is a contiguous non-empty sequence of characters within a string.
 *
 * ! 3 <= s.length <= 50
 * ! s consists of only lowercase English letters.
 */

class Solution {
public:
    int maximumLength(std::string s)
    {
        const int n = s.size();
        std::unordered_map<std::string, int> map;
        int result = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (s[j] != s[i])
                    break;

                if (++map[s[i] + std::to_string(j - i + 1)] >= 3) {
                    result = std::max(result, j - i + 1);
                }
            }
        }
        return result;
    }
};