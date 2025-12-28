#include <string>

/**
 * 实现一个算法，确定一个字符串 s 的所有字符是否全都不同。
 *
 * ! 0 <= len(s) <= 100
 * ! s[i]仅包含小写字母
 * ! 如果你不使用额外的数据结构，会很加分。
 */

class Solution {
public:
    bool isUnique(std::string astr)
    {
        int mask = 0;
        for (const auto& c : astr) {
            const int index = c - 'a';
            if ((mask >> index) & 1)
                return false;

            mask |= (1 << index);
        }
        return true;
    }
};