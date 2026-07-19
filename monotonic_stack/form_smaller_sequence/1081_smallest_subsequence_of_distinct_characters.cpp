#include <array>
#include <string>

/**
 * Given a string s, return the lexicographically smallest subsequence of s that contains all the
 * distinct characters of s exactly once.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of lowercase English letters.
 *
 * ! This question is the same as LC.316.
 */

class Solution {
public:
    std::string smallestSubsequence(std::string& s)
    {
        static constexpr int R = 26;
        const int n = s.size();
        std::array<int, R> last{};
        last.fill(-1);
        for (int i = 0; i < n; ++i) {
            last[s[i] - 'a'] = i;
        }
        std::array<bool, R> inResult{};
        std::string result;
        for (int i = 0; i < n; ++i) {
            if (inResult[s[i] - 'a'])
                continue;

            while (!result.empty() && s[i] < result.back() && i < last[result.back() - 'a']) {
                inResult[result.back() - 'a'] = false;
                result.pop_back();
            }
            result.push_back(s[i]);
            inResult[s[i] - 'a'] = true;
        }
        return result;
    }
};
