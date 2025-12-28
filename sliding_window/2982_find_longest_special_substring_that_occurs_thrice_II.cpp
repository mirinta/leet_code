#include <array>
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
 * ! 3 <= s.length <= 5 * 10^5
 * ! s consists of only lowercase English letters.
 */

class Solution {
public:
    int maximumLength(std::string s)
    {
        // count[i][j] = occurrences of substring equal to (i+'a')*j
        const int n = s.size();
        std::array<std::unordered_map<int, int>, 26> count;
        int i = 0;
        int result = -1;
        while (i < n) {
            int j = i + 1;
            while (j < n && s[j] == s[i]) {
                j++;
            }
            const int index = s[i] - 'a';
            const int length = j - i;
            // case1: 1 valid substring with length L
            // case2: 2 valid substrings with length L-1
            // case3: 3 valid substrings with length L-2
            // case4: 4 valid substrings with length L-3
            // ...
            // since we need to find the max length and the num of substrings must be >= 3
            // then we only need to consider case1/2/3
            if (++count[index][length] >= 3) {
                result = std::max(result, length);
            }
            if (length > 1 && (count[index][length - 1] += 2) >= 3) {
                result = std::max(result, length - 1);
            }
            if (length > 2) {
                result = std::max(result, length - 2);
            }
            i = j;
        }
        return result;
    }
};