#include <string>
#include <unordered_map>

/**
 * 在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。
 *
 * ! 0 <= s 的长度 <= 50000
 */

class Solution {
public:
    char firstUniqChar(std::string s)
    {
        std::unordered_map<char, int> freq;
        for (const auto& c : s) {
            freq[c]++;
        }
        for (const auto& c : s) {
            if (freq[c] == 1)
                return c;
        }
        return ' ';
    }
};