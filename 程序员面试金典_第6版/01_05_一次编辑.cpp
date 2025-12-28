#include <string>

/**
 * 字符串有三种编辑操作:插入一个英文字符、删除一个英文字符或者替换一个英文字符。
 * 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
 */

class Solution {
public:
    bool oneEditAway(std::string first, std::string second)
    {
        if (first.size() < second.size()) {
            std::swap(first, second);
        }
        if (first.size() - second.size() > 1)
            return false;

        if (first.size() == second.size()) {
            int count = 0;
            for (int i = 0; i < first.size(); ++i) {
                if (first[i] != second[i]) {
                    count++;
                }
                if (count > 1)
                    return false;
            }
            return true;
        }
        int count = 0;
        for (int i = 0, j = 0; i < first.size(); ++i) {
            if (first[i] != second[j]) {
                count++;
            } else {
                j++;
            }
            if (count > 1)
                return false;
        }
        return true;
    }
};