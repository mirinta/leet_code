#include <array>
#include <string>

/**
 * Given a string s and an integer k, return true if you can use all the characters in s to
 * construct k palindrome strings or false otherwise.
 *
 * ! 1 <= s.length <= 10^5
 * ! s consists of lowercase English letters.
 * ! 1 <= k <= 10^5
 */

class Solution {
public:
    bool canConstruct(std::string s, int k)
    {
        if (s.size() < k)
            return false;

        if (s.size() == k)
            return true;

        std::array<int, 26> count{};
        for (const auto& c : s) {
            count[c - 'a']++;
        }
        int odd = 0;
        for (const auto& val : count) {
            odd += val % 2;
        }
        return odd <= k;
    }
};