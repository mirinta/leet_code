#include <algorithm>
#include <string>
#include <vector>

/**
 * Special binary strings are binary strings with the following two properties:
 *
 * - The number of 0's is equal to the number of 1's.
 *
 * - Every prefix of the binary string has at least as many 1's as 0's.
 *
 * You are given a special binary string s.
 *
 * A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are
 * consecutive if the last character of the first string is exactly one index before the first character of the second
 * string.
 *
 * Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.
 *
 * ! 1 <= s.length <= 50
 * ! s[i] is either '0' or '1'.
 * ! s is a special binary string.
 */

class Solution {
public:
    std::string makeLargestSpecial(std::string& s)
    {
        // each special string must start with 1 and must end with 0
        // the pattern is: s = 1[x]0
        // if x can be divided into more valid substrings,
        // say x = ABCD where A, B, C and D are the lexicographically largest special strings
        // then result = 1[sort and concatenate ABCD]0
        if (s.size() == 2)
            return s;

        const int n = s.size();
        std::vector<std::string> strs;
        for (int i = 0, sum = 0, start = 0; i < n; ++i) {
            sum += s[i] == '1' ? 1 : -1;
            if (sum != 0)
                continue;

            auto sub = s.substr(start + 1, i - start - 1);
            strs.push_back("1" + makeLargestSpecial(sub) + "0");
            start = i + 1;
        }
        std::sort(strs.begin(), strs.end(), std::greater<>());
        std::string result;
        for (const auto& s : strs) {
            result.append(s);
        }
        return result;
    }
};