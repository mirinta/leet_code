#include <algorithm>
#include <string>

/**
 * Given a string s and an integer k, reverse the first k characters for every 2k characters
 * counting from the start of the string.
 *
 * If there are fewer than k characters left, reverse all of them. If there are less than 2k but
 * greater than or equal to k characters, then reverse the first k characters and leave the other as
 * original.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of only lowercase English letters.
 * ! 1 <= k <= 10^4
 */

class Solution {
public:
    std::string reverseStr(std::string s, int k)
    {
        const int n = s.size();
        for (int i = 0; i < n; i += 2 * k) {
            const int j = std::min(n - 1, i + k - 1);
            if (i < j) {
                std::reverse(s.begin() + i, s.begin() + j + 1);
            }
        }
        return s;
    }
};