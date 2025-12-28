#include <string>
#include <unordered_map>

/**
 * 给定一个字符串，编写一个函数判定其是否为某个回文串的排列之一。
 *
 * 回文串是指正反两个方向都一样的单词或短语。排列是指字母的重新排列。
 *
 * 回文串不一定是字典当中的单词。
 */

class Solution {
public:
    bool canPermutePalindrome(std::string s)
    {
        std::unordered_map<char, int> map;
        for (const auto& c : s) {
            map[c]++;
        }
        bool foundOddFreq = false;
        for (const auto& [c, freq] : map) {
            if (!(freq & 1))
                continue;

            if (foundOddFreq)
                return false;

            foundOddFreq = true;
        }
        return true;
    }
};