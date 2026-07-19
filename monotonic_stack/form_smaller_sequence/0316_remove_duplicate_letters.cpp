#include <array>
#include <string>

/**
 * Given a string s, remove duplicate letters so that every letter appears once and only once. You
 * must make sure your result is the smallest in lexicographical order among all possible results.
 *
 * ! 1 <= s.length <= 10^4
 * ! s consists of lowercase English letters.
 *
 * ! This question is the same as LC.1081.
 */

class Solution {
public:
    std::string removeDuplicateLetters(std::string& s)
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
