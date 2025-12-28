#include <string>

/**
 * You are given a string s and an integer k.
 *
 * Define a function distance(s1, s2) between two strings s1 and s2 of the same length n as:
 *
 * The sum of the minimum distance between s1[i] and s2[i] when the characters from 'a' to 'z' are
 * placed in a cyclic order, for all i in the range [0, n - 1]. For example, distance("ab", "cd") ==
 * 4, and distance("a", "z") == 1.
 *
 * You can change any letter of s to any other lowercase English letter, any number of times.
 *
 * Return a string denoting the lexicographically smallest string t you can get after some changes,
 * such that distance(s, t) <= k.
 *
 * ! 1 <= s.length <= 100
 * ! 0 <= k <= 2000
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    std::string getSmallestString(std::string s, int k)
    {
        if (k == 0)
            return s;

        const int n = s.size();
        std::string result(s);
        for (int i = 0; i < n && k > 0; ++i) {
            if (dist(s[i], 'a') <= k) {
                result[i] = 'a';
            } else {
                const char c1 = (s[i] - 'a' + k) % 26 + 'a';
                const char c2 = (s[i] - 'a' - k + 26) % 26 + 'a';
                result[i] = std::min(c1, c2);
            }
            k -= dist(s[i], result[i]);
        }
        return result;
    }

private:
    int dist(char c1, char c2)
    {
        return std::min(std::abs(c1 - c2), 26 - std::abs(c1 - c2));
    }
};