#include <string>
#include <vector>

/**
 * A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding
 * itself).
 *
 * Given a string s, return the longest happy prefix of s. Return an empty string "" if no such
 * prefix exists.
 *
 * ! 1 <= s.length <= 10^5
 * ! s contains only lowercase English letters.
 */

class Solution {
public:
    std::string longestPrefix(std::string s)
    {
        const int n = s.size();
        std::vector<int> next(n, 0); // KMP's "next" array
        next[0] = 0;
        for (int i = 1; i < n; ++i) {
            int L = next[i - 1];
            while (L >= 1 && s[L] != s[i]) {
                L = next[L - 1];
            }
            next[i] = L + (s[L] == s[i]);
        }
        return s.substr(0, next[n - 1]);
    }
};