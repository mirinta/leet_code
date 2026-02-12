#include <array>
#include <string>

/**
 * You are given a string s consisting of lowercase English letters.
 *
 * A substring of s is called balanced if all distinct characters in the substring appear the same number of times.
 *
 * Return the length of the longest balanced substring of s.
 *
 * ! 1 <= s.length <= 1000
 * ! s consists of lowercase English letters.
 */

class Solution {
public:
    int longestBalanced(std::string& s)
    {
        const int n = s.size();
        std::array<int, 26> count{};
        int result = 0;
        for (int i = 0; i < n; ++i) {
            count.fill(-1);
            for (int j = i; j < n; ++j) {
                count[s[j] - 'a']++;
                if (isValid(count)) {
                    result = std::max(result, j - i + 1);
                }
            }
        }
        return result;
    }

private:
    bool isValid(const std::array<int, 26>& count)
    {
        int check = -1;
        for (const auto& val : count) {
            if (val == -1)
                continue;

            if (check == -1) {
                check = val;
            }
            if (val != check)
                return false;
        }
        return true;
    }
};
