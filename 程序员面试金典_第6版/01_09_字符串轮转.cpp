#include <string>

/**
 * 字符串轮转。给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成（比如，waterbottle是erbottlewat旋转后的字符串）。
 *
 * ! 字符串长度在[0, 100000]范围内。
 * ! 你能只调用一次检查子串的方法吗？
 */

class Solution {
public:
    bool isFlipedString(std::string s1, std::string s2)
    {
        if (s1.empty() && s2.empty())
            return true;

        if (s1.size() != s2.size())
            return false;

        return (s1 + s1).find(s2) != std::string::npos;
    }
};