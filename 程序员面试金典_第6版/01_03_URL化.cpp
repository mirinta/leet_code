#include <string>

/**
 * URL化。编写一种方法，将字符串中的空格全部替换为%20。假定该字符串尾部有足够的空间存放新增字符，并且知道字符串的“真实”长度。（注：用Java实现的话，请使用字符数组实现，以便直接在数组上操作。）
 *
 * ! 字符串长度在 [0, 500000] 范围内。
 */

class Solution {
public:
    std::string replaceSpaces(std::string S, int length)
    {
        return approach2(S, length);
    }

private:
    std::string approach2(std::string& s, int length)
    {
        int j = s.size() - 1;
        for (int i = length - 1; i >= 0; --i) {
            if (s[i] != ' ') {
                s[j--] = s[i];
            } else {
                s[j--] = '0';
                s[j--] = '2';
                s[j--] = '%';
            }
        }
        return s.substr(j + 1);
    }

    std::string approach1(const std::string& s, int length)
    {
        std::string result;
        for (int i = 0; i < length; ++i) {
            if (s[i] != ' ') {
                result.push_back(s[i]);
            } else {
                result.append("%20");
            }
        }
        return result;
    }
};