#include <algorithm>
#include <array>
#include <string>

/**
 * You are given two strings s1 and s2 of equal length. A string swap is an operation where you
 * choose two indices in a string (not necessarily different) and swap the characters at these
 * indices.
 *
 * Return true if it is possible to make both strings equal by performing at most one string swap on
 * exactly one of the strings. Otherwise, return false.
 *
 * ! 1 <= s1.length, s2.length <= 100
 * ! s1.length == s2.length
 * ! s1 and s2 consist of only lowercase English letters.
 */

class Solution {
public:
    bool areAlmostEqual(std::string s1, std::string s2)
    {
        if (s1.size() != s2.size())
            return false;

        std::array<int, 26> count{};
        const int n = s1.size();
        int countDiff = 0;
        for (int i = 0; i < n; ++i) {
            count[s1[i] - 'a']++;
            count[s2[i] - 'a']--;
            countDiff += s1[i] != s2[i];
            if (countDiff > 2)
                return false;
        }
        if (std::any_of(count.begin(), count.end(), [](const int val) { return val > 0; }))
            return false;

        return countDiff == 0 || countDiff == 2;
    }
};
