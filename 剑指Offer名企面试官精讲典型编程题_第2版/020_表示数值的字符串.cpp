#include <string>

/**
 * 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
 *
 * 数值（按顺序）可以分成以下几个部分：
 * 1. 若干空格
 * 2. 一个 小数 或者 整数
 * 3. （可选）一个 'e' 或 'E' ，后面跟着一个 整数
 * 4. 若干空格
 *
 * 小数（按顺序）可以分成以下几个部分：
 * 1. （可选）一个符号字符（'+' 或 '-'）
 * 2. 下述格式之一：
 *          1. 至少一位数字，后面跟着一个点 '.'
 *          2. 至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
 *          3. 一个点 '.' ，后面跟着至少一位数字
 *
 * 整数（按顺序）可以分成以下几个部分：
 * 1. 可选）一个符号字符（'+' 或 '-'）
 * 2. 至少一位数字
 *
 * 部分数值列举如下：
 * ["+100", "5e2", "-123", "3.1416", "-1E-16", "0123"]
 *
 * 部分非数值列举如下：
 * ["12e", "1a3.14", "1.2.3", "+-5", "12e+5.4"]
 *
 * ! 1 <= s.length <= 20
 * ! s 仅含英文字母（大写和小写），数字（0-9），加号 '+' ，减号 '-' ，空格 ' ' 或者点 '.' 。
 *
 * ! 本题与LC 65类似，区别是本题要考虑空格。
 */

class Solution {
public:
    bool isNumber(const std::string& s)
    {
        if (s.empty())
            return false;

        int start = 0;
        int end = s.size() - 1;
        while (start < s.size() && s[start] == ' ') {
            start++;
        }
        while (end >= 0 && s[end] == ' ') {
            end--;
        }
        if (start > end)
            return false; // 全是空格

        // [sign][0-9][.][0-9][E/e][sign][0-9]
        bool seenDigit = false;
        bool seenDot = false;
        bool seenExponent = false;
        for (int i = start; i <= end; ++i) {
            const auto& c = s[i];
            if (c >= '0' && c <= '9') {
                seenDigit = true;
            } else if (c == '+' || c == '-') {
                // 符号只能在首位，或紧跟在E/e之后
                if (i > start && s[i - 1] != 'E' && s[i - 1] != 'e')
                    return false;

            } else if (c == '.') {
                // 最多只能有1个小数点，且不能在E/e之后
                if (seenDot || seenExponent)
                    return false;

                seenDot = true;
            } else if (c == 'E' || c == 'e') {
                // 最多只能有1个E/e，且必须在数字之后
                if (seenExponent || !seenDigit)
                    return false;

                seenExponent = true;
                seenDigit = false; // E/e之后必须出现数字，因此重置seenDigit
            } else {
                return false;
            }
        }
        return seenDigit;
    }
};