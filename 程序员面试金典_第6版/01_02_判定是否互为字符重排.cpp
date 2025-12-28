#include <algorithm>
#include <array>
#include <string>

/**
 * 给定两个由小写字母组成的字符串 s1 和
 * s2，请编写一个程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。
 *
 * ! 0 <= len(s1) <= 100
 * ! 0 <= len(s2) <= 100
 */

class Solution {
public:
    bool CheckPermutation(std::string s1, std::string s2)
    {
        std::array<int, 26> count{};
        for (const auto& c : s1) {
            count[c - 'a']++;
        }
        for (const auto& c : s2) {
            const int index = c - 'a';
            if (count[index] == 0)
                return false;

            count[index]--;
        }
        return std::all_of(count.begin(), count.end(), [](const auto& v) { return v == 0; });
    }
};