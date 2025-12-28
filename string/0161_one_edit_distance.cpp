#include <string>

/**
 * Given two strings s and t, return true if they are both one edit distance apart, otherwise return
 * false.
 *
 * A string s is said to be one distance apart from a string t if you can:
 *
 * - Insert exactly one character into s to get t.
 *
 * - Delete exactly one character from s to get t.
 *
 * - Replace exactly one character of s with a different character to get t.
 *
 * ! 0 <= s.length, t.length <= 10^4
 * ! s and t consist of lowercase letters, uppercase letters, and digits.
 */

class Solution {
public:
    bool isOneEditDistance(std::string s, std::string t)
    {
        if (s == t)
            return false;

        const int m = s.size();
        const int n = t.size();
        if (m < n)
            return isOneEditDistance(t, s);

        if (m - n >= 2)
            return false;

        for (int i = 0; i < n; ++i) {
            if (s[i] == t[i])
                continue;

            // case1: m == n (same length)
            // s: X X i i+1 X X
            // t: X X j j+1 X X
            // once we make s[i] = t[j]
            // we need to make sure s[i+1::] = t[j+1::]
            if (m == n)
                return s.substr(i + 1) == t.substr(i + 1);

            // case2: m > n
            // s: X X i i+1 X X
            // t: X X j X X
            // remove s[i] from s,
            // we need to make sure s[i+1::] = t[j::]
            return s.substr(i + 1) == t.substr(i);
        }
        return true;
    }
};
