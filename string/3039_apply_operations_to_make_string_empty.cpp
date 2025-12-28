#include <algorithm>
#include <array>
#include <string>

/**
 * You are given a string s.
 *
 * Consider performing the following operation until s becomes empty:
 *
 * For every alphabet character from 'a' to 'z', remove the first occurrence of that character in s
 * (if it exists). For example, let initially s = "aabcbbca". We do the following operations:
 *
 * - Remove the underlined characters s = "aabcbbca". The resulting string is s = "abbca".
 *
 * - Remove the underlined characters s = "abbca". The resulting string is s = "ba".
 *
 * - Remove the underlined characters s = "ba". The resulting string is s = "".
 *
 * Return the value of the string s right before applying the last operation. In the example above,
 * answer is "ba".
 *
 * ! 1 <= s.length <= 5 * 10^5
 * ! s consists only of lowercase English letters.
 */

class Solution {
public:
    std::string lastNonEmptyString(std::string s)
    {
        const int n = s.size();
        std::array<std::pair<int, int>, 26> info; // <freq, last>
        std::fill(info.begin(), info.end(), std::make_pair(0, -1));
        for (int i = 0; i < n; ++i) {
            info[s[i] - 'a'].first++;
            info[s[i] - 'a'].second = i;
        }
        int maxFreq = 0;
        for (const auto& [freq, last] : info) {
            maxFreq = std::max(maxFreq, freq);
        }
        std::string result;
        for (int i = 0; i < 26; ++i) {
            if (info[i].first == maxFreq) {
                result.push_back('a' + i);
            }
        }
        std::sort(result.begin(), result.end(),
                  [&info](const char c1, const char c2) { return info[c1 - 'a'] < info[c2 - 'a']; });
        return result;
    }
};