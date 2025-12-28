#include <string>

/**
 * 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
 */

class Solution {
public:
    std::string replaceSpace(std::string s)
    {
        approach2(s);
        return s;
    }

private:
    // approach 1: straightforward
    std::string approach1(const std::string& s)
    {
        if (s.empty())
            return {};

        std::string result;
        for (const auto& c : s) {
            if (c == ' ') {
                result.append("%20");
            } else {
                result.push_back(c);
            }
        }
        return result;
    }

    // approach 2: in-place modification
    void approach2(std::string& s)
    {
        if (s.empty())
            return;

        int numOfSpaces = 0;
        for (const auto& i : s) {
            if (i == ' ') {
                numOfSpaces++;
            }
        }
        if (numOfSpaces == 0)
            return;

        int originEnd = s.size() - 1;
        s.resize(s.size() + 2 * numOfSpaces);
        int newEnd = s.size() - 1;
        while (originEnd >= 0 && newEnd > originEnd) {
            if (s[originEnd] != ' ') {
                s[newEnd--] = s[originEnd--];
            } else {
                s[newEnd--] = '0';
                s[newEnd--] = '2';
                s[newEnd--] = '%';
                originEnd--;
            }
        }
    }
};
