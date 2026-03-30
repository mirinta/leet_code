#include <array>
#include <string>

/**
 * You are given two strings s1 and s2, both of length n, consisting of lowercase English letters.
 *
 * You can apply the following operation on any of the two strings any number of times:
 *
 * - Choose any two indices i and j such that i < j and the difference j - i is even, then swap the two characters at
 * those indices in the string.
 *
 * Return true if you can make the strings s1 and s2 equal, and false otherwise.
 *
 * ! n == s1.length == s2.length
 * ! 1 <= n <= 10^5
 * ! s1 and s2 consist only of lowercase English letters.
 */

class Solution {
public:
    bool canBeEqual(std::string& s1, std::string& s2)
    {
        return helper(s1) == helper(s2);
    }

private:
    std::array<std::array<int, 26>, 2> helper(const std::string& s)
    {
        const int n = s.size();
        std::array<std::array<int, 26>, 2> count{}; // <even, odd>
        for (int i = 0; i < n; ++i) {
            count[i % 2][s[i] - 'a']++;
        }
        return count;
    }
};